---
id: MP-WORKSPACES-LIFECYCLE-0.2.6
status: draft
runbook: docs/program/23-runbooks/workspaces-lifecycle.md
phase: "0.2.6 — root command wiring wave"
owners:
  - runtime
adrs:
  - docs/program/22-adr/ADR-006-unified-rpc.md
  - docs/program/22-adr/ADR-007-workspace-isolation.md
  - docs/program/22-adr/ADR-011-contract-baseline-lock.md
  - docs/program/22-adr/ADR-012-audit-convergence-gates.md
spec_anchors:
  - yai-law/registry/commands.v1.json
  - docs/program/23-runbooks/workspaces-lifecycle-command-map.v2.md
target_group: root
target_command_count: 200
---

# MP-WORKSPACES-LIFECYCLE-0.2.6

## Objective
Plan and execute real runtime wiring for group `root` without contract drift.

Group mission: Root routing/authority edge surfaces.

## Scope (Planned)
- Canonical target group: `root`
- Canonical command count: `200`
- Family distribution (top): `authority_*` (20), `channel_*` (20), `context_*` (20), `envelope_*` (20), `handshake_*` (20), `plane_*` (20), `relay_*` (20), `router_*` (20), `session_*` (20), `trace_*` (19)
- Delivery model: keep all registered commands invocable; implement selected handlers first; missing handlers remain deterministic (`nyi` equivalent).

## Representative command_id set
- `yai.root.authority_attach`
- `yai.root.authority_audit`
- `yai.root.authority_authorize`
- `yai.root.authority_checkpoint`
- `yai.root.authority_detach`
- `yai.root.authority_forward`
- `yai.root.authority_gate`
- `yai.root.authority_guard`
- `yai.root.authority_inspect`
- `yai.root.authority_ping`
- `yai.root.authority_reconcile`
- `yai.root.authority_recover`
- `yai.root.authority_refresh`
- `yai.root.authority_relay`
- `yai.root.authority_rotate`

## Definition of Done
- [ ] Group `root` commands remain discoverable in CLI help.
- [ ] No `unknown command` for registered IDs in this group.
- [ ] Selected real handlers are wired end-to-end (CLI -> SDK -> Root -> Kernel/Engine).
- [ ] Non-implemented commands return deterministic error model (`ok/error/nyi` mapping).
- [ ] Evidence pointers/logs for executed commands are archived.

## Required evidence (to fill at execution time)
- [ ] Build/test logs for touched repos.
- [ ] Command execution matrix for this group.
- [ ] Runtime logs with deterministic outcomes.
- [ ] Audit mapping updates (claim-by-claim if Gate A scope is impacted).

## Risks and follow-ups
- Risk: wide family surface may hide semantic collisions.
- Mitigation: implement by family slices, keeping contract fixed.
- Follow-up: chain next MP after this group reaches stable deterministic behavior.

## Closure decision
Status: `PLANNED` (no runtime implementation claimed in this MP).
