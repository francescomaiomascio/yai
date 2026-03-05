---
id: MP-WORKSPACES-LIFECYCLE-INDEX
status: active
runbook: docs/program/23-runbooks/workspaces-lifecycle.md
phase: index
adrs:
  - docs/program/22-adr/ADR-006-unified-rpc.md
  - docs/program/22-adr/ADR-007-workspace-isolation.md
  - docs/program/22-adr/ADR-011-contract-baseline-lock.md
  - docs/program/22-adr/ADR-012-audit-convergence-gates.md
spec_anchors:
  - yai-law/registry/commands.v1.json
  - docs/program/23-runbooks/workspaces-lifecycle-command-map.v2.md
issues:
  - "N/A: lifecycle-scope index"
---

# Workspaces Lifecycle Milestone Packs

Runbook reference:
- `docs/program/23-runbooks/workspaces-lifecycle.md`

Scope rule:
- This track contains only WS-lifecycle governance/runtime surfaces.
- Non-WS command expansion packs were moved to:
  - `docs/program/24-milestone-packs/command-coverage/README.md`

WS-lifecycle sequence (active in this track):
- `docs/program/24-milestone-packs/workspaces-lifecycle/MP-WORKSPACES-LIFECYCLE-0.2.1.md` (control)
- `docs/program/24-milestone-packs/workspaces-lifecycle/MP-WORKSPACES-LIFECYCLE-0.2.2.md` (governance)
- `docs/program/24-milestone-packs/workspaces-lifecycle/MP-WORKSPACES-LIFECYCLE-0.2.3.md` (inspect)
- `docs/program/24-milestone-packs/workspaces-lifecycle/MP-WORKSPACES-LIFECYCLE-0.2.4.md` (kernel)
- `docs/program/24-milestone-packs/workspaces-lifecycle/MP-WORKSPACES-LIFECYCLE-0.2.5.md` (lifecycle)
- `docs/program/24-milestone-packs/workspaces-lifecycle/MP-WORKSPACES-LIFECYCLE-0.2.6.md` (root)
- `docs/program/24-milestone-packs/workspaces-lifecycle/MP-WORKSPACES-LIFECYCLE-0.2.7.md` (verify)

Notes:
- `0.2.1` and `0.2.2` are already delivered/merged in prior execution.
- Command-catalog completeness (`2800`) is tracked separately from WS-lifecycle closure.
