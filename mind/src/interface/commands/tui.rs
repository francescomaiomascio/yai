use crate::interface::config::RuntimeConfig;
use crate::interface::tui::app::ViewKind;
use crate::interface::tui::snapshot::snapshot_for_view;
use anyhow::{bail, Result};

pub fn run(cfg: &RuntimeConfig, ws: &str) -> Result<()> {
    crate::interface::tui::run(ws, cfg)
}

pub fn snapshot(cfg: &RuntimeConfig, ws: &str, view: &str) -> Result<()> {
    let v = match view {
        "overview" => ViewKind::Overview,
        "graph" => ViewKind::Graph,
        "events" => ViewKind::Events,
        "logs" => ViewKind::Logs,
        "db" => ViewKind::Db,
        "providers" => ViewKind::Providers,
        "contracts" => ViewKind::Contracts,
        "chat" => ViewKind::Chat,
        _ => bail!("unknown view: {view}"),
    };
    let snap = snapshot_for_view(cfg, ws, v)?;
    println!("{}", serde_json::to_string_pretty(&snap)?);
    Ok(())
}
