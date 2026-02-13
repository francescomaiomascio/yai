use std::path::PathBuf;

use crate::types::WsId;

/// Workspace-aware filesystem layout.
/// Single source of truth for all on-disk locations.
#[derive(Debug, Clone)]
pub struct Paths {
    pub root: PathBuf, // e.g. ~/.yai
    pub run: PathBuf,  // e.g. ~/.yai/run
    pub ws: WsId,
}

impl Paths {
    /// Default root is ~/.yai (override later via config)
    pub fn new_default(ws: WsId) -> Self {
        let home = std::env::var("HOME").unwrap_or_else(|_| ".".into());
        let root = PathBuf::from(home).join(".yai");
        let run = root.join("run");
        Self { root, run, ws }
    }

    /// ~/.yai/run/<ws_id>/
    pub fn ws_run_dir(&self) -> PathBuf {
        self.run.join(&self.ws)
    }

    /// ~/.yai/run/<ws_id>/control.sock (kernel control plane)
    pub fn control_sock(&self) -> PathBuf {
        self.ws_run_dir().join("control.sock")
    }

    /// ~/.yai/run/<ws_id>/events.log
    pub fn events_log(&self) -> PathBuf {
        self.ws_run_dir().join("events.log")
    }

    /// ~/.yai/run/<ws_id>/semantic.sqlite (workspace graph store)
    pub fn semantic_sqlite(&self) -> PathBuf {
        self.ws_run_dir().join("semantic.sqlite")
    }

    /// ~/.yai/run/<ws_id>/graph/ (workspace graph dir)
    pub fn graph_dir(&self) -> PathBuf {
        self.ws_run_dir().join("graph")
    }
}
