//! mind/src/transport/rpc/uds_client.rs
//! Kernel control-plane client (NDJSON, strict v1)

use anyhow::{Context, Result};
use serde_json::{json, Value};
use std::io::{BufRead, BufReader, Write};
use std::os::unix::net::UnixStream;
use std::path::{Path, PathBuf};

/// Canonical control socket:
/// ~/.yai/run/<ws>/control.sock
fn control_socket_path(run_dir: &Path, ws: &str) -> PathBuf {
    run_dir.join(ws).join("control.sock")
}

/// Send raw envelope to Kernel and return raw JSON response.
pub fn send_envelope(
    yai_root: &Path,
    ws: &str,
    envelope: Value,
) -> Result<Value> {
    let run_dir = yai_root.join("run");
    let sock = control_socket_path(&run_dir, ws);

    let mut stream = UnixStream::connect(&sock)
        .with_context(|| format!("connect control socket: {}", sock.display()))?;

    let payload = serde_json::to_string(&envelope)
        .context("serialize control envelope")?;

    stream.write_all(payload.as_bytes())?;
    stream.write_all(b"\n")?;
    stream.flush().ok();

    let mut reader = BufReader::new(stream);
    let mut line = String::new();
    reader.read_line(&mut line)
        .context("read control response")?;

    let resp: Value =
        serde_json::from_str(&line).context("parse control response")?;

    Ok(resp)
}

/// Convenience wrapper for status
pub fn send_status(yai_root: &Path, ws: &str) -> Result<Value> {
    let envelope = json!({
        "v": 1,
        "ws_id": ws,
        "arming": false,
        "request": { "type": "status" }
    });

    send_envelope(yai_root, ws, envelope)
}

/// Convenience wrapper for ping
pub fn send_ping(yai_root: &Path, ws: &str) -> Result<Value> {
    let envelope = json!({
        "v": 1,
        "ws_id": ws,
        "arming": false,
        "request": { "type": "ping" }
    });

    send_envelope(yai_root, ws, envelope)
}
