use crate::cli::config::RuntimeConfig;
use crate::transport::rpc::uds_client;
use anyhow::Result;
use serde_json::Value;
use std::path::PathBuf;

pub fn run(cfg: &RuntimeConfig, ws: &str, json: bool) -> Result<()> {
    // ~/.yai
    let yai_root = cfg.yai_root();

    // Prova a chiedere status al Kernel
    match uds_client::send_status(&yai_root, ws) {
        Ok(resp) => {
            if json {
                println!("{}", resp);
                return Ok(());
            }

            print_human(ws, &resp);
        }

        Err(_) => {
            if json {
                println!(r#"{{"v":1,"type":"status","state":"down","ws_id":"{}"}}"#, ws);
            } else {
                println!("ws: {} (kernel down)", ws);
            }
        }
    }

    Ok(())
}

fn print_human(ws: &str, resp: &Value) {
    let t = resp.get("type").and_then(|v| v.as_str()).unwrap_or("");

    match t {
        "status" => {
            let state = resp.get("state")
                .and_then(|v| v.as_str())
                .unwrap_or("unknown");

            println!("ws: {}", ws);
            println!("state: {}", state);
        }

        "error" => {
            let msg = resp.get("message")
                .and_then(|v| v.as_str())
                .unwrap_or("unknown error");

            println!("status error: {}", msg);
        }

        _ => {
            println!("unexpected response: {}", resp);
        }
    }
}
