---
id: RB-WORKSPACE-DATA-SINKS
status: draft
depends_on:
  - RB-DATA-PLANE
---

# Workspace Data Sinks (DP companion)

This runbook complements DP-1 with workspace-focused sink boundaries.

## Canonical sink focus
- workspace operational state sink,
- authority sink bindings at workspace scope,
- apply/attachment state sink links,
- workspace artifact metadata refs.

## Guardrails
1. Workspace scope is mandatory.
2. No direct consumer write bypass.
3. Path-jail and identity checks before sink writes.
4. Deterministic status and reason in runtime replies.

Detailed backend mapping is deferred to DP-2 and DP-3.
