# Workspace Peer Orchestration Law Alignment (OP-1)

Status: active  
Owner: runtime  
Effective date: 2026-03-11

## Purpose

Capture the OP-1 coordination semantics that must be consumable by
`yai-law` slices without over-claiming full policy closure.

## OP-1 signals relevant to law

- workspace peer membership exists as explicit coordination relation
- peer role/scope is explicit (`peer_role`, `peer_scope`)
- peer coverage is explicit (`coverage_ref`)
- overlap/conflict expectation is explicit (`overlap_state`)
- per-peer backlog/health is observable (`peer_state`, backlog counters)

## Law-facing implications

Future law slices can govern:

- which peer roles can attach to which workspace classes
- which coverage scopes are acceptable for a governance profile
- what overlap states require review/escalation
- how degraded/disconnected peer states affect governance readiness

## Explicit boundary

OP-1 does not embed law decisions in runtime orchestration.
It introduces structured runtime signals so law can govern them in later waves.

MF-2 coordination extension:
- mesh coordination membership is owner-anchored and scope-governed;
- peer awareness metadata is coordination input, not sovereign authority;
- ordering/replay/overlap/conflict coordination signals are review/adjudication
  inputs and not final law verdicts.

SW-1 compatibility:
- multi-peer orchestration signals are owner-consumed inputs;
- canonical authority/truth and final adjudication remain workspace owner-side.

## References

- `docs/architecture/workspace-peer-orchestration-model.md`
- `docs/source-attachment-governance-model.md`
