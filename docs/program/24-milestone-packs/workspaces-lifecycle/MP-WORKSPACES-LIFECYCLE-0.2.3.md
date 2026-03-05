---
id: MP-WORKSPACES-LIFECYCLE-0.2.3
status: draft
runbook: docs/program/23-runbooks/workspaces-lifecycle.md
phase: "0.2.3 — inspect command wiring wave"
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
target_group: inspect
target_command_count: 200
---

# MP-WORKSPACES-LIFECYCLE-0.2.3

## Objective
Plan and execute real runtime wiring for group `inspect` without contract drift.

Group mission: Inspection, logs, status and telemetry surfaces.

## Scope (Planned)
- Canonical target group: `inspect`
- Canonical command count: `200`
- Family distribution (top): `events_*` (21), `logs_*` (21), `status_*` (21), `health_*` (20), `jobs_*` (20), `metrics_*` (20), `routes_*` (20), `sessions_*` (20), `trace_*` (20), `alerts_*` (16)
- Delivery model: keep all registered commands invocable; implement selected handlers first; missing handlers remain deterministic (`nyi` equivalent).

## Representative command_id set
- `yai.inspect.alerts_audit`
- `yai.inspect.alerts_compare`
- `yai.inspect.alerts_diff`
- `yai.inspect.alerts_export`
- `yai.inspect.alerts_filter`
- `yai.inspect.alerts_logs`
- `yai.inspect.alerts_monitor`
- `yai.inspect.alerts_query`
- `yai.inspect.alerts_snapshot`
- `yai.inspect.alerts_status`
- `yai.inspect.alerts_stream`
- `yai.inspect.alerts_summarize`
- `yai.inspect.alerts_tail`
- `yai.inspect.alerts_trace`
- `yai.inspect.alerts_validate`

## Definition of Done
- [ ] Group `inspect` commands remain discoverable in CLI help.
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
