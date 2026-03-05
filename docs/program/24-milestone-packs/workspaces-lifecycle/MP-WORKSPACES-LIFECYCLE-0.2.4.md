---
id: MP-WORKSPACES-LIFECYCLE-0.2.4
status: draft
runbook: docs/program/23-runbooks/workspaces-lifecycle.md
phase: "0.2.4 — kernel command wiring wave"
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
target_group: kernel
target_command_count: 200
---

# MP-WORKSPACES-LIFECYCLE-0.2.4

## Objective
Plan and execute real runtime wiring for group `kernel` without contract drift.

Group mission: Kernel enforcement and workspace boundary surfaces.

## Scope (Planned)
- Canonical target group: `kernel`
- Canonical command count: `200`
- Family distribution (top): `ws_*` (21), `boundary_*` (20), `enforce_*` (20), `mount_*` (20), `policy_*` (20), `quota_*` (20), `resource_*` (20), `route_*` (20), `session_*` (20), `audit_*` (18)
- Delivery model: keep all registered commands invocable; implement selected handlers first; missing handlers remain deterministic (`nyi` equivalent).

## Representative command_id set
- `yai.kernel.audit_apply`
- `yai.kernel.audit_attach`
- `yai.kernel.audit_create`
- `yai.kernel.audit_destroy`
- `yai.kernel.audit_detach`
- `yai.kernel.audit_enforce`
- `yai.kernel.audit_freeze`
- `yai.kernel.audit_guard`
- `yai.kernel.audit_list`
- `yai.kernel.audit_ping`
- `yai.kernel.audit_reconcile`
- `yai.kernel.audit_reset`
- `yai.kernel.audit_restore`
- `yai.kernel.audit_snapshot`
- `yai.kernel.audit_status`

## Definition of Done
- [ ] Group `kernel` commands remain discoverable in CLI help.
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
