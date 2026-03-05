---
id: MP-WORKSPACES-LIFECYCLE-0.2.5
status: draft
runbook: docs/program/23-runbooks/workspaces-lifecycle.md
phase: "0.2.5 — lifecycle command wiring wave"
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
target_group: lifecycle
target_command_count: 200
---

# MP-WORKSPACES-LIFECYCLE-0.2.5

## Objective
Plan and execute real runtime wiring for group `lifecycle` without contract drift.

Group mission: Stack/workspace lifecycle orchestration surfaces.

## Scope (Planned)
- Canonical target group: `lifecycle`
- Canonical command count: `200`
- Family distribution (top): `daemon_*` (20), `engine_*` (20), `mind_*` (20), `plane_*` (20), `runtime_*` (20), `service_*` (20), `session_*` (20), `stack_*` (20), `workspace_*` (20), `profile_*` (17)
- Delivery model: keep all registered commands invocable; implement selected handlers first; missing handlers remain deterministic (`nyi` equivalent).

## Representative command_id set
- `yai.lifecycle.daemon_audit`
- `yai.lifecycle.daemon_bootstrap`
- `yai.lifecycle.daemon_cleanup`
- `yai.lifecycle.daemon_down`
- `yai.lifecycle.daemon_drain`
- `yai.lifecycle.daemon_heal`
- `yai.lifecycle.daemon_migrate`
- `yai.lifecycle.daemon_pause`
- `yai.lifecycle.daemon_prepare`
- `yai.lifecycle.daemon_reconcile`
- `yai.lifecycle.daemon_reload`
- `yai.lifecycle.daemon_restart`
- `yai.lifecycle.daemon_resume`
- `yai.lifecycle.daemon_roll`
- `yai.lifecycle.daemon_shutdown`

## Definition of Done
- [ ] Group `lifecycle` commands remain discoverable in CLI help.
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
