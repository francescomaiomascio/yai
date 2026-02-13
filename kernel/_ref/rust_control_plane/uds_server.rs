//! mind/src/transport/rpc/uds_server.rs
//! DEPRECATED — Kernel owns control plane.
//!
//! This server must NOT be started.
//! The control UDS is now exclusively owned by the C Kernel.

use anyhow::{anyhow, Result};
use std::path::Path;
use std::sync::Arc;

pub trait RpcHandler: Send + Sync + 'static {}

/// This function is intentionally disabled.
/// If called, it means architecture boundaries are being violated.
pub async fn serve<P: AsRef<Path>>(_socket_path: P, _handler: Arc<dyn RpcHandler>) -> Result<()> {
    Err(anyhow!(
        "uds_server is disabled. Control plane is owned by Kernel."
    ))
}
