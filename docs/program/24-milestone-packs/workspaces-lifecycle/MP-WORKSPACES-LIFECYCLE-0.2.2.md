---
id: MP-WORKSPACES-LIFECYCLE-0.2.2
status: draft
runbook: docs/program/23-runbooks/workspaces-lifecycle.md
phase: "0.2.2 — governance command wiring wave"
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
target_group: governance
target_command_count: 200
---

# MP-WORKSPACES-LIFECYCLE-0.2.2

## Objective
Plan and execute real runtime wiring for group `governance` without contract drift.

Group mission: Governance and policy decision surfaces.

## Scope (Planned)
- Canonical target group: `governance`
- Canonical command count: `200`
- Family distribution (top): `baseline_*` (21), `claim_*` (21), `decision_*` (21), `evidence_*` (21), `exception_*` (21), `policy_*` (21), `scope_*` (21), `assertion_*` (20), `controlset_*` (20), `assert_*` (1)
- Delivery model: keep all registered commands invocable; implement selected handlers first; missing handlers remain deterministic (`nyi` equivalent).

## Representative command_id set
- `yai.governance.assert`
- `yai.governance.assertion_approve`
- `yai.governance.assertion_assert`
- `yai.governance.assertion_attest`
- `yai.governance.assertion_audit`
- `yai.governance.assertion_claim`
- `yai.governance.assertion_compare`
- `yai.governance.assertion_controls`
- `yai.governance.assertion_deny`
- `yai.governance.assertion_exception`
- `yai.governance.assertion_lock`
- `yai.governance.assertion_publish`
- `yai.governance.assertion_reconcile`
- `yai.governance.assertion_report`
- `yai.governance.assertion_review`

## Definition of Done
- [ ] Group `governance` commands remain discoverable in CLI help.
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
