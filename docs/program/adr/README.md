---
id: ADR-README
status: active
law_refs:
  - ../law/foundation/invariants/I-001-traceability.md
---
# ADR Index

Architecture Decision Records (ADRs) capture irreversible or high-impact technical choices.

An ADR should answer:
- what was decided,
- why alternatives were rejected,
- what consequences are accepted,
- which law/spec anchors govern the decision.

## Canonical ADR set

- `adr-runtime-001-single-runtime.md`
- `adr-runtime-002-root-entrypoint.md`
- `adr-runtime-003-kernel-authority.md`
- `adr-orchestration-004-engine-execution.md`
- `adr-runtime-005-mind-proposer.md`
- `adr-protocol-006-unified-rpc.md`
- `adr-workspace-007-workspace-isolation.md`
- `adr-workspace-008-connection-lifecycle.md`
- `adr-orchestration-009-engine-attachment.md`
- `adr-runtime-010-boot-entrypoint.md`
- `adr-contracts-011-contract-runbook-lock.md`
- `adr-program-012-audit-convergence-gates.md`
- `adr-distributed-013-distributed-acquisition-centralized-control.md`
- `adr-distributed-014-secure-peering-plane.md`
- `adr-distributed-015-daemon-architecture-slice.md`
- `adr-governance-016-global-to-edge-policy-hierarchy-lock.md`
- `adr-distributed-017-delegated-edge-enforcement-architecture.md`
- `adr-runtime-018-process-and-asset-runtime-observation-architecture.md`
- `adr-distributed-019-edge-binding-and-action-point-architecture.md`
- `adr-workspace-020-workspace-authority-and-truth-plane.md`
- `adr-governance-021-workspace-to-edge-policy-distribution.md`
- `adr-distributed-022-edge-policy-validity-expiry-refresh.md`
- `adr-distributed-023-governed-sovereign-mesh-foundation.md`
- `adr-distributed-024-mesh-discovery-foundation.md`
- `adr-distributed-025-mesh-coordination-foundation.md`
- `adr-distributed-026-sovereign-mesh-authority-foundation.md`
- `adr-protocol-027-secure-overlay-transport-plane.md`
- `adr-distributed-028-owner-remote-peer-ingress.md`
- `adr-governance-029-overlay-integration.md`
- `adr-governance-030-source-and-edge-query-surfaces.md`
- `adr-data-031-unified-graph-workspace-edge-runtime.md`
- `adr-intelligence-032-ai-grounding-governed-case-state.md`

## Template policy

The ADR template is canonical only in:
- `docs/program/templates/adr/ADR-000-template.md`

No template copy should be kept inside this ADR directory.

## Maintenance notes

When adding a new ADR:
- update this index,
- ensure law/spec references are explicit,
- add downstream runbook linkage when available.

Program-level convergence governance is defined in:
- `docs/program/reports/audit-convergence/EXECUTION-PLAN-v0.1.0.md`
