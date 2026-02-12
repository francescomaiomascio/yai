use crate::interface::config::RuntimeConfig;
use crate::lifecycle::awareness::{awareness_log_path, run_awareness_with_config, AwarenessConfig};
use crate::memory::graph::facade::{
    ActivationPolicy, GraphEdge, GraphExportFormat, GraphFacade, GraphNode, GraphScope,
    NeighborFilters,
};
use anyhow::{bail, Result};
use serde_json::Value;
use std::collections::HashSet;
use std::path::PathBuf;
use std::time::{SystemTime, UNIX_EPOCH};

fn resolve_scope(cfg: &RuntimeConfig, ws: Option<&str>, global: bool) -> Result<GraphScope> {
    if global {
        if ws.is_some() {
            bail!("use either --ws or --global");
        }
        return Ok(GraphScope::Global);
    }
    let scope_ws = ws
        .map(ToString::to_string)
        .unwrap_or_else(|| cfg.ws_default.clone());
    Ok(GraphScope::Workspace(scope_ws))
}

pub fn add_node(
    cfg: &RuntimeConfig,
    ws: Option<&str>,
    global: bool,
    id: &str,
    kind: &str,
    meta: &str,
) -> Result<()> {
    let scope = resolve_scope(cfg, ws, global)?;
    let meta_val: Value = serde_json::from_str(meta)?;
    let ts = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap_or_default()
        .as_secs();
    GraphFacade::put_node(
        scope,
        GraphNode {
            id: id.to_string(),
            kind: kind.to_string(),
            meta: meta_val,
            last_seen: ts,
        },
    )?;
    println!("ok node id={id}");
    Ok(())
}

pub fn add_edge(
    cfg: &RuntimeConfig,
    ws: Option<&str>,
    global: bool,
    src: &str,
    dst: &str,
    rel: &str,
    weight: f32,
) -> Result<()> {
    let scope = resolve_scope(cfg, ws, global)?;
    let edge_id = format!("edge:{}:{}:{}", rel, src, dst);
    GraphFacade::put_edge(
        scope,
        GraphEdge {
            id: edge_id.clone(),
            src: src.to_string(),
            dst: dst.to_string(),
            rel: rel.to_string(),
            weight,
            meta: Value::Null,
        },
    )?;
    println!("ok edge id={edge_id}");
    Ok(())
}

pub fn query(cfg: &RuntimeConfig, ws: Option<&str>, global: bool, text: &str, k: usize) -> Result<()> {
    let scope = resolve_scope(cfg, ws, global)?;
    let mut seeds = Vec::new();
    let sub = GraphFacade::neighbors(scope.clone(), text, 0, NeighborFilters::default())?;
    if !sub.nodes.is_empty() {
        seeds.push((text.to_string(), 1.0));
    } else {
        for node in GraphFacade::neighbors(scope.clone(), text, 1, NeighborFilters::default())?.nodes {
            seeds.push((node.id, 1.0));
            if seeds.len() >= k {
                break;
            }
        }
    }
    if seeds.is_empty() {
        // fallback to deterministic first nodes by lexicographic order
        let stats = GraphFacade::stats(scope.clone())?;
        println!(
            "nodes: 0\nedges: 0\nnote: no direct seed match for text={text}; backend={}",
            stats.backend
        );
        return Ok(());
    }
    let result = GraphFacade::activate(
        scope,
        &seeds,
        ActivationPolicy {
            top_n: k * 2,
            ..ActivationPolicy::default()
        },
    )?;
    println!("nodes: {}", result.nodes.len());
    for n in result.nodes {
        let score = result.scores.get(&n.id).copied().unwrap_or(0.0);
        println!("node {} kind={} score={:.4}", n.id, n.kind, score);
    }
    println!("edges: {}", result.edges.len());
    for e in result.edges {
        println!("edge {} -> {} rel={} w={}", e.src, e.dst, e.rel, e.weight);
    }
    Ok(())
}

pub fn stats(cfg: &RuntimeConfig, ws: Option<&str>, global: bool) -> Result<()> {
    let scope = resolve_scope(cfg, ws, global)?;
    let s = GraphFacade::stats(scope)?;
    println!("scope: {}", s.scope);
    println!("backend: {}", s.backend);
    println!("nodes: {}", s.nodes);
    println!("edges: {}", s.edges);
    for (k, v) in s.categories {
        println!("category.{k}: {v}");
    }
    Ok(())
}

pub fn node(cfg: &RuntimeConfig, ws: Option<&str>, global: bool, id: &str, limit: usize) -> Result<()> {
    let scope = resolve_scope(cfg, ws, global)?;
    let node = GraphFacade::get_node(scope.clone(), id)?;
    let Some(node) = node else {
        bail!("node not found: {id}");
    };
    let sub = GraphFacade::neighbors(scope, id, 1, NeighborFilters::default())?;
    println!("{}", serde_json::to_string_pretty(&node)?);
    let mut in_edges = Vec::new();
    let mut out_edges = Vec::new();
    for e in sub.edges {
        if e.src == id {
            out_edges.push(e);
        } else if e.dst == id {
            in_edges.push(e);
        }
    }
    in_edges.sort_by(|a, b| a.id.cmp(&b.id));
    out_edges.sort_by(|a, b| a.id.cmp(&b.id));
    in_edges.truncate(limit);
    out_edges.truncate(limit);
    println!("in_edges: {}", in_edges.len());
    for e in in_edges {
        println!("in  {} <- {} rel={} w={}", e.dst, e.src, e.rel, e.weight);
    }
    println!("out_edges: {}", out_edges.len());
    for e in out_edges {
        println!("out {} -> {} rel={} w={}", e.src, e.dst, e.rel, e.weight);
    }
    Ok(())
}

pub fn neighbors(
    cfg: &RuntimeConfig,
    ws: Option<&str>,
    global: bool,
    id: &str,
    depth: usize,
    rels: &[String],
    kinds: &[String],
) -> Result<()> {
    let scope = resolve_scope(cfg, ws, global)?;
    let filters = NeighborFilters {
        rels: if rels.is_empty() {
            None
        } else {
            Some(rels.iter().cloned().collect::<HashSet<_>>())
        },
        kinds: if kinds.is_empty() {
            None
        } else {
            Some(kinds.iter().cloned().collect::<HashSet<_>>())
        },
        directed: false,
    };
    let sg = GraphFacade::neighbors(scope, id, depth, filters)?;
    println!("nodes: {}", sg.nodes.len());
    println!("edges: {}", sg.edges.len());
    for n in sg.nodes {
        println!("node {} kind={}", n.id, n.kind);
    }
    for e in sg.edges {
        println!("edge {} -> {} rel={} w={}", e.src, e.dst, e.rel, e.weight);
    }
    Ok(())
}

pub fn export(
    cfg: &RuntimeConfig,
    ws: Option<&str>,
    global: bool,
    format: &str,
    out: &str,
) -> Result<()> {
    let scope = resolve_scope(cfg, ws, global)?;
    let fmt = match format {
        "dot" => GraphExportFormat::Dot,
        "jsonl" => GraphExportFormat::Jsonl,
        _ => bail!("unsupported export format: {format}"),
    };
    let out_path = PathBuf::from(out);
    GraphFacade::export(scope, fmt, &out_path)?;
    let size = std::fs::metadata(&out_path)?.len();
    println!("exported {} bytes to {}", size, out_path.display());
    Ok(())
}

pub fn awareness(_cfg: &RuntimeConfig, ws: &str, tick_ms: u64, max_steps: Option<u64>) -> Result<()> {
    run_awareness_with_config(
        ws,
        AwarenessConfig {
            tick_ms,
            max_steps,
        },
    )?;
    let p = awareness_log_path(ws);
    println!("awareness_log={}", p.display());
    Ok(())
}
