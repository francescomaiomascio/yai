---
id: RB-EVENT-EVIDENCE-PERSISTENCE
status: draft
depends_on:
  - RB-DATA-PLANE
---

# Event and Evidence Persistence (DP companion)

This runbook scopes DP event/evidence persistence boundaries.

## Canonical classes
- Event Log
- Resolution/Evidence Log

## Requirements
1. Append/read contracts must be deterministic.
2. Evidence pointers must remain traceable and stable.
3. Failure semantics must use canonical runtime error mapping.
4. Retention controls must be explicit and auditable.

Topology and placement are defined by DP-3:
- `docs/program/23-runbooks/data-plane-storage-topology.md`

DP-4 hardens these sinks in implementation.
