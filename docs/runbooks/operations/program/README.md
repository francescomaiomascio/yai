---
id: RB-RUNBOOKS-README
status: active
adr_refs:
  - docs/program/adr/ADR-011-contract-baseline-lock.md
  - docs/program/adr/ADR-012-audit-convergence-gates.md
decisions:
  - docs/program/adr/ADR-011-contract-baseline-lock.md
  - docs/program/adr/ADR-012-audit-convergence-gates.md
---

# Runbooks

Runbooks translate decisions into phased, repeatable execution.

A good runbook must be deterministic:
- clear preconditions,
- explicit procedure,
- verifiable outcomes,
- rollback/failure handling.

## Canonical operational runbooks (active truth path)

- `docs/runbooks/operations/program/contract-baseline-lock.md`
- `docs/runbooks/operations/program/data-plane.md`
- `docs/runbooks/operations/program/data-plane-storage-classes.md`
- `docs/runbooks/operations/program/data-plane-storage-topology.md`
- `docs/runbooks/operations/program/workspace-data-sinks.md`
- `docs/runbooks/operations/program/evidence-and-event-persistence.md`
- `docs/runbooks/operations/program/governance-and-compliance-persistence.md`
- `docs/runbooks/operations/program/authority-and-artifact-persistence.md`
- `docs/runbooks/operations/program/brain-memory-and-graph-sinks.md`
- `docs/runbooks/operations/program/data-surfaces-and-operator-query-model.md`
- `docs/runbooks/operations/program/workspace-command-taxonomy-refoundation.md`
- `docs/runbooks/operations/program/workspace-runtime-command-mapping-and-canonicalization.md`
- `docs/runbooks/operations/program/data-plane-qualification-and-closure.md`
- `docs/runbooks/operations/program/enforcement-to-record-persistence.md`
- `docs/runbooks/operations/program/graph-materialization-from-runtime-records.md`
- `docs/runbooks/operations/program/db-first-read-path-cutover.md`
- `docs/runbooks/operations/program/filesystem-governance-state-decommission.md`
- `docs/runbooks/operations/program/filesystem-cleanup-and-archive-execution.md`
- `docs/runbooks/operations/program/data-lifecycle-retention-and-tiering.md`
- `docs/runbooks/operations/program/unified-runtime-topology-refoundation.md`
- `docs/runbooks/operations/program/operations.md`
- `docs/runbooks/operations/program/edge-binding-and-action-points-baseline.md`
- `docs/runbooks/operations/program/workspace-authority-truth-plane-baseline.md`
- `docs/runbooks/operations/program/governed-sovereign-mesh-baseline.md`
- `docs/runbooks/operations/program/mesh-discovery-foundation-baseline.md`
- `docs/runbooks/operations/program/mesh-coordination-foundation-baseline.md`
- `docs/runbooks/operations/program/sovereign-mesh-authority-baseline.md`
- `docs/runbooks/operations/program/secure-overlay-transport-baseline.md`
- `docs/runbooks/operations/program/owner-remote-peer-ingress-baseline.md`
- `docs/runbooks/operations/program/overlay-integration-baseline.md`
- `docs/runbooks/operations/program/source-and-edge-query-surfaces-baseline.md`
- `docs/runbooks/operations/program/unified-graph-workspace-edge-baseline.md`
- `docs/runbooks/operations/program/ai-grounding-governed-case-state-baseline.md`
- `docs/runbooks/operations/program/qualification-lan-baseline.md`

These runbooks are expected to reflect:
- unified runtime ownership (`core`, `exec`, `data`, `graph`, `knowledge`),
- workspace-first binding,
- canonical readiness/binding semantics.

## Historical / superseded runbooks (non-canonical)

The following remain for traceability only and must not be used as current
operational guidance for unified runtime behavior:

- `docs/runbooks/operations/program/root-hardening.md`
- `docs/runbooks/operations/program/workspaces-lifecycle.md`
- `docs/runbooks/operations/program/engine-attach.md`
- `docs/runbooks/operations/program/mind-redis-stm.md`
- `docs/runbooks/operations/program/kernel-sovereignty.md`

## Program Convergence Backbone

Program-level target-state and wave ordering are defined in:
- `docs/program/reports/audit-convergence/EXECUTION-PLAN-v0.1.0.md`
- `docs/program/reports/audit-convergence/AUDIT-CONVERGENCE-MATRIX-v0.1.0.md`

Runbook phase closure should reference claim IDs from:
- `ops/evidence/validation/audits/claims/infra-grammar.v0.1.json`

## Template

- `docs/program/templates/runbooks/RB-000-template.md`

## Traceability expectation

Runbooks should link:
- upstream ADRs and law/spec anchors,
- downstream milestone packs as phases are delivered.
