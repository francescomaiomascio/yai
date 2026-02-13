//! mind/src/transport/rpc/uds_server.rs
//! UDS RPC server + robust request parsing (strict + loose + legacy).

use crate::transport::rpc::protocol::{
    Request, Response, RpcRequestEnvelope, RPC_PROTOCOL_VERSION,
};
use anyhow::{Context, Result};
use serde::Deserialize;
use std::{future::Future, path::Path, pin::Pin, sync::Arc};
use tokio::io::{AsyncBufReadExt, AsyncWriteExt, BufReader};
use tokio::net::unix::{OwnedReadHalf, OwnedWriteHalf};
use tokio::net::{UnixListener, UnixStream};

pub struct RpcInbound {
    pub request: Request,
    pub arming: bool,
    pub role: Option<String>,
    pub ws_id: Option<String>,
}

// ---------------------------
// Handler trait (no extra deps)
// ---------------------------

pub type BoxFut<'a, T> = Pin<Box<dyn Future<Output = T> + Send + 'a>>;

pub trait RpcHandler: Send + Sync + 'static {
    fn handle<'a>(&'a self, inbound: RpcInbound) -> BoxFut<'a, Result<Response>>;
}

// ---------------------------
// Server loop
// ---------------------------

pub async fn serve<P: AsRef<Path>>(socket_path: P, handler: Arc<dyn RpcHandler>) -> Result<()> {
    let sock = socket_path.as_ref();

    // remove stale socket
    if tokio::fs::metadata(sock).await.is_ok() {
        let _ = tokio::fs::remove_file(sock).await;
    }

    let listener =
        UnixListener::bind(sock).with_context(|| format!("bind uds socket: {}", sock.display()))?;

    loop {
        let (stream, _addr) = listener.accept().await.context("uds accept")?;
        let h = handler.clone();

        tokio::spawn(async move {
            if let Err(e) = handle_stream(stream, h).await {
                // non facciamo crashare tutto: log minimale
                eprintln!("[uds_server] connection error: {e:#}");
            }
        });
    }
}

async fn handle_stream(stream: UnixStream, handler: Arc<dyn RpcHandler>) -> Result<()> {
    let (read_half, mut write_half) = stream.into_split();
    let mut reader = BufReader::new(read_half);

    loop {
        match read_request(&mut reader).await {
            Ok(inbound) => {
                let resp = handler
                    .handle(inbound)
                    .await
                    .context("rpc handler failed")?;
                write_response(&mut write_half, &resp).await?;
            }
            Err(e) => {
                // EOF pulito
                if is_eof(&e) {
                    return Ok(());
                }
                // parse/other error: chiudiamo la connessione (meglio che restare in loop “rotto”)
                return Err(e);
            }
        }
    }
}

fn is_eof(e: &anyhow::Error) -> bool {
    let s = e.to_string();
    s.contains("rpc eof") || s.contains("early eof") || s.contains("connection reset")
}

// ---------------------------
// Robust parsing helpers
// ---------------------------

#[derive(Debug, Deserialize)]
struct RpcRequestEnvelopeLoose {
    // accetta anche "version"
    #[serde(alias = "version")]
    pub v: serde_json::Value,

    #[serde(default)]
    pub arming: bool,

    #[serde(default)]
    pub role: Option<String>,

    // accetta ws_id, wsId, workspace_id
    #[serde(default, alias = "wsId", alias = "workspace_id")]
    pub ws_id: Option<String>,

    pub request: serde_json::Value,
}

fn parse_version(v: &serde_json::Value) -> Option<u8> {
    match v {
        serde_json::Value::Number(n) => n.as_u64().and_then(|x| u8::try_from(x).ok()),
        serde_json::Value::String(s) => s.parse::<u8>().ok(),
        _ => None,
    }
}

fn preview_json(v: &serde_json::Value, max: usize) -> String {
    let s = serde_json::to_string(v).unwrap_or_else(|_| "<unserializable>".to_string());
    if s.len() > max {
        format!("{}…", &s[..max])
    } else {
        s
    }
}

fn pascal_to_snake(s: &str) -> String {
    let mut out = String::with_capacity(s.len() + 8);
    for (i, ch) in s.chars().enumerate() {
        if ch.is_ascii_uppercase() {
            if i != 0 {
                out.push('_');
            }
            out.push(ch.to_ascii_lowercase());
        } else {
            out.push(ch);
        }
    }
    out
}

fn pascal_to_dot(s: &str) -> String {
    pascal_to_snake(s).replace('_', ".")
}

fn try_parse_request_candidates(candidates: Vec<serde_json::Value>) -> Result<Request> {
    for c in candidates {
        if let Ok(req) = serde_json::from_value::<Request>(c) {
            return Ok(req);
        }
    }
    anyhow::bail!("no compatible request encoding matched")
}

/// Prova a deserializzare `Request` con più forme tollerate:
/// 1) parse diretto (il formato “canonico” di Request)
/// 2) request come stringa
/// 3) request object con tag alternativi (op/kind/cmd/name/type) normalizzati
fn parse_request_compat(v: &serde_json::Value) -> Result<Request> {
    // 1) Canonico (il formato attuale server)
    if let Ok(req) = serde_json::from_value::<Request>(v.clone()) {
        return Ok(req);
    }

    // 2) Stringa (se mai arrivasse)
    if let Some(s) = v.as_str() {
        return serde_json::from_value::<Request>(serde_json::Value::String(s.to_string()))
            .context("parse request from string");
    }

    // 3) Object
    if let Some(obj) = v.as_object() {
        // 3a) Externally-tagged enum: { "VariantName": { ... } }
        if obj.len() == 1 {
            let (variant, inner) = obj.iter().next().unwrap();

            // se inner non è object, proviamo comunque a usarlo come payload
            let inner_obj = inner.as_object();

            // proviamo più normalizzazioni del nome variante
            let mut tags = vec![
                variant.to_string(),
                variant.to_lowercase(),
                pascal_to_snake(variant),
                pascal_to_dot(variant),
            ];
            tags.dedup();

            let mut candidates = Vec::new();

            for tag in tags {
                // candidato A: {"type": tag, ...inner_fields} (flatten)
                if let Some(inner_obj) = inner_obj {
                    let mut flat = serde_json::Map::new();
                    flat.insert("type".to_string(), serde_json::Value::String(tag.clone()));
                    for (k, val) in inner_obj {
                        flat.insert(k.clone(), val.clone());
                    }
                    candidates.push(serde_json::Value::Object(flat));
                }

                // candidato B: {"type": tag, "payload": inner}
                candidates.push(serde_json::json!({ "type": tag, "payload": inner }));

                // candidato C: {"type": tag, "data": inner}
                candidates.push(serde_json::json!({ "type": tag, "data": inner }));

                // candidato D: {"op": tag, ...} (se lato server hai tag diversi)
                if let Some(inner_obj) = inner_obj {
                    let mut op_flat = serde_json::Map::new();
                    op_flat.insert("op".to_string(), serde_json::Value::String(tag.clone()));
                    for (k, val) in inner_obj {
                        op_flat.insert(k.clone(), val.clone());
                    }
                    candidates.push(serde_json::Value::Object(op_flat));
                }
            }

            if let Ok(req) = try_parse_request_candidates(candidates) {
                return Ok(req);
            }
        }

        // 3b) Object con tag esplicito (type/op/kind/cmd/name)
        let tag = obj
            .get("type")
            .or_else(|| obj.get("op"))
            .or_else(|| obj.get("kind"))
            .or_else(|| obj.get("cmd"))
            .or_else(|| obj.get("name"))
            .and_then(|x| x.as_str());

        if let Some(tag) = tag {
            let tag_val = serde_json::Value::String(tag.to_string());
            let mut normalized = obj.clone();
            for k in ["type", "op", "kind", "cmd", "name"] {
                normalized.entry(k.to_string()).or_insert(tag_val.clone());
            }
            let norm_val = serde_json::Value::Object(normalized);
            if let Ok(req) = serde_json::from_value::<Request>(norm_val) {
                return Ok(req);
            }
        }
    }

    anyhow::bail!("unsupported request shape: {}", preview_json(v, 240));
}

// ---------------------------
// Public read/write API
// ---------------------------

pub async fn read_request(reader: &mut BufReader<OwnedReadHalf>) -> Result<RpcInbound> {
    let mut line = String::new();
    let n = reader.read_line(&mut line).await.context("read rpc line")?;

    if n == 0 {
        anyhow::bail!("rpc eof");
    }

    if line.trim().is_empty() {
        anyhow::bail!("empty rpc request");
    }

    let trimmed = line.trim_end();
    let preview_line = if trimmed.len() > 240 {
        format!("{}…", &trimmed[..240])
    } else {
        trimmed.to_string()
    };

    // 1) Strict envelope (il tuo path “ideale”)
    let strict = serde_json::from_str::<RpcRequestEnvelope>(&line);
    if let Ok(envelope) = strict {
        if envelope.v != RPC_PROTOCOL_VERSION {
            anyhow::bail!(
                "rpc protocol mismatch: client v{} != server v{}",
                envelope.v,
                RPC_PROTOCOL_VERSION
            );
        }
        return Ok(RpcInbound {
            request: envelope.request,
            arming: envelope.arming,
            role: envelope.role,
            ws_id: envelope.ws_id,
        });
    }

    // 2) Loose envelope (alias + diagnostica + request compat)
    if let Ok(loose) = serde_json::from_str::<RpcRequestEnvelopeLoose>(&line) {
        let v = parse_version(&loose.v).unwrap_or(0);
        if v != RPC_PROTOCOL_VERSION {
            anyhow::bail!(
                "rpc protocol mismatch: client v{} != server v{}",
                v,
                RPC_PROTOCOL_VERSION
            );
        }

        let request = parse_request_compat(&loose.request).with_context(|| {
            format!(
                "parse rpc request (envelope.value): {}",
                preview_json(&loose.request, 240)
            )
        })?;

        return Ok(RpcInbound {
            request,
            arming: loose.arming,
            role: loose.role,
            ws_id: loose.ws_id,
        });
    }

    // 3) Legacy: la riga è direttamente un Request
    let req: Request = serde_json::from_str(&line)
        .with_context(|| format!("parse rpc request (legacy): {preview_line}"))?;

    Ok(RpcInbound {
        request: req,
        arming: false,
        role: None,
        ws_id: None,
    })
}

pub async fn write_response(writer: &mut OwnedWriteHalf, resp: &Response) -> Result<()> {
    let payload = serde_json::to_string(resp).context("serialize rpc response")?;
    writer.write_all(payload.as_bytes()).await?;
    writer.write_all(b"\n").await?;
    writer.flush().await?;
    Ok(())
}
