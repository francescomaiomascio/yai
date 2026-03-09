---
id: RB-BRAIN-MEMORY-GRAPH-SINKS
status: draft
depends_on:
  - RB-DATA-PLANE
  - RB-MIND-REDIS-STM
---

# Brain Memory and Graph Sinks (DP companion)

This runbook clarifies Brain relation to Data Plane without making Brain the DP center.

## Canonical classes
- Brain Graph Memory (persistent truth)
- Transient Cognition / STM (non-authoritative, short-lived)

## Boundary rules
1. Graph truth and transient cognition remain distinct classes.
2. Transient backend state cannot override authoritative persistent state.
3. Backend technology choices are role-bound, not model-defining.

DP-7 delivers full integration.
