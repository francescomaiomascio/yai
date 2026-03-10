---
id: workspace-verticalization-wsv8-closure-plan-v0.1.0
status: active
owner: runtime-governance
updated: 2026-03-10
scope: [yai, yai-law, yai-cli, yai-sdk]
related:
  - docs/program/reports/workspace-verticalization-gap-audit-v0.1.0.md
  - docs/program/reports/workspace-verticalization-gap-classification-matrix-v0.1.0.md
---

# WSV-7.5 -> WSV-8 Closure Plan (v0.1.0)

This plan translates WSV-7 manual findings into implementation-grade WSV-8 work packages.
WSV-8 is fix/closure wave; this document is the scoped execution map.

## WSV-8 success criteria

WSV-8 is considered closed only if:
1. runtime endpoint is reachable after `lifecycle up` in validation environment,
2. workspace create/open/set leads to observable bound state and artifacts,
3. representative families (`graph`, `db`, `data`, `policy`) execute with live non-`SERVER_UNAVAILABLE` responses,
4. CLI readiness/liveness story is coherent across lifecycle/doctor/inspect/status,
5. SDK typed-surface smoke is deterministic in scripted wave execution.

## Work packages

### WP-1 Runtime readiness and control-plane convergence
- Priority: `P0`
- Severity addressed: `S1`
- Repos: `yai`, `yai-cli`
- Symptoms resolved:
  - lifecycle up returns non-ready and downstream commands fail `SERVER_UNAVAILABLE`
  - doctor/inspect runtime unreachable in same session.
- Fix scope:
  - harden runtime bring-up and control socket readiness handshake,
  - enforce reliable readiness transition before ws command path is treated as live,
  - tighten CLI lifecycle result semantics against actual control-plane reachability.
- Acceptance proof:
  - manual pack sections B/C/D/E/G produce at least one non-`SERVER_UNAVAILABLE` successful call,
  - `yai --verbose-contract runtime ping` returns non-server-off status in live run.

### WP-2 Workspace bind/persistence post-condition hardening
- Priority: `P0`
- Severity addressed: `S1`
- Repos: `yai`
- Symptoms resolved:
  - no workspace data root/graph/events artifacts after create/set path.
- Fix scope:
  - enforce post-conditions for `create/open/set`,
  - verify persistence path initialization and artifact sinks under active workspace,
  - provide explicit failure reason when post-conditions cannot be met.
- Acceptance proof:
  - evidence checks in manual pack section J succeed (`~/.yai/run/data/<ws>`, graph/events files exist),
  - workspace inspect/status show bound capability state.

### WP-3 CLI output contract coherence for readiness/binding
- Priority: `P1`
- Severity addressed: `S2`
- Repos: `yai-cli` (+ runtime truth source in `yai`)
- Symptoms resolved:
  - lifecycle output implies reachability while doctor/inspect report unreachable.
- Fix scope:
  - unify rendering rules for liveness/readiness/binding across lifecycle/status/inspect/doctor,
  - ensure hints are consistent and actionable.
- Acceptance proof:
  - CLI guardrails updated and green,
  - same run shows no contradictory readiness/liveness interpretation.

### WP-4 Family execution diagnostics and routing hardening
- Priority: `P1`
- Severity addressed: `S2`
- Repos: `yai`, `yai-cli`
- Symptoms resolved:
  - all families fail with generic error; poor family-level diagnostics.
- Fix scope:
  - preserve canonical routing, but improve diagnostics by failure class,
  - ensure family preflight identifies missing workspace bind vs runtime unavailable vs protocol failure.
- Acceptance proof:
  - representative commands from each family return differentiated, actionable errors or successful outputs,
  - manual execution report shows reduced ambiguous failures.

### WP-5 SDK smoke determinism
- Priority: `P2`
- Severity addressed: `S3`
- Repos: `yai-sdk`
- Symptoms resolved:
  - one non-deterministic scripted failure in wave run.
- Fix scope:
  - stabilize smoke setup/cleanup around workspace context state,
  - add deterministic pre-clean / isolation in test runner path.
- Acceptance proof:
  - repeated `make test` runs in wave context pass consistently.

### WP-6 Composition-backed family debt reduction
- Priority: `P2`
- Severity addressed: `S3`
- Repos: `yai`, `yai-cli`, `yai-sdk`, `yai-law`
- Symptoms resolved:
  - partial composition in `ws db` / `ws recovery` / `ws knowledge`.
- Fix scope:
  - evaluate direct runtime ID promotion opportunities,
  - update mapping/registry/sdk headers where direct backing replaces composition.
- Acceptance proof:
  - matrix debt rows downgraded or removed,
  - docs/manual pack updated to reflect direct-backed paths.

### WP-7 Compatibility and docs/help polish
- Priority: `P3`
- Severity addressed: `S4`
- Repos: `yai-cli`, `yai-sdk`, docs cross-repo
- Symptoms resolved:
  - compatibility/fallback noise in operator guidance.
- Fix scope:
  - keep fallback path but reduce canonical-path ambiguity in help/docs/examples.
- Acceptance proof:
  - docs/guardrails show canonical path first and fallback as explicit secondary path.

## Repo ownership map for WSV-8 execution

- `yai`: WP-1, WP-2, WP-4, WP-6
- `yai-cli`: WP-1, WP-3, WP-4, WP-7
- `yai-sdk`: WP-5, WP-6, WP-7
- `yai-law`: WP-6 (registry/mapping parity validation)

## Recommended execution order

1. WP-1
2. WP-2
3. WP-3
4. WP-4
5. WP-5
6. WP-6
7. WP-7

## Closure recommendation

WSV-8 should be launched as a focused implementation wave on WP-1..WP-4 first.
Without those, manual execution remains blocked and rich workspace inspectability cannot be proven operationally.
