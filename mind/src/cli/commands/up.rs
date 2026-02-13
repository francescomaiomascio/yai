use crate::cli::commands::logs;
use crate::cli::config::RuntimeConfig;
use crate::control::events::EventBus;
use crate::control::workspace;
use anyhow::Result;

#[derive(Debug, Clone)]
pub struct UpRuntime {
    pub ws: String,
    pub monitor: bool,
    pub ai: bool,
    pub no_engine: bool,
    pub no_mind: bool,
    pub detach: bool,
    pub build: bool,
    pub timeout_ms: Option<u64>,
}

pub fn run(cfg: &RuntimeConfig, args: &UpRuntime) -> Result<()> {
    let ws = &args.ws;

    if args.monitor {
        super::monitor::spawn_external_terminal(cfg, ws)?;
    }

    eprintln!("[yai up ws={ws}] starting runtime (kernel+engine)");
    let bus = EventBus::new(cfg.run_dir.clone(), ws.to_string());
    let opts = workspace::StartOpts {
        build: args.build,
        no_engine: args.no_engine,
        no_mind: true,
        ai: false,
        timeout_ms: args.timeout_ms.unwrap_or(5000),
    };
    workspace::start_stack(cfg, ws, &opts, &bus)?;

    if args.detach {
        println!("up complete for ws={} (detached)", ws);
        return Ok(());
    }

    // Attach mode: follow logs
    let mut components = vec!["kernel"];
    components.push("daemon");
    if !args.no_engine {
        components.push("engine");
    }
    logs::follow_components(cfg, ws, &components)?;
    Ok(())
}
