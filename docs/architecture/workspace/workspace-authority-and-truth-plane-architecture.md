# Workspace Authority and Truth Plane Model (SW-1)

Status: active  
Owner: runtime  
Effective date: 2026-03-11

## Purpose

Lock the owner workspace runtime as the sovereign center of the system:

- sovereign authority plane
- canonical truth plane

This boundary ensures distributed edge execution never becomes distributed
truth.

## Sovereign Authority Plane (owner-side)

Owner workspace runtime is the only final authority for:

- global workspace policy
- trust/grant issuance and revocation
- attachability and ingest adjudication
- final conflict adjudication
- canonical case progression decisions

## Canonical Truth Plane (owner-side)

Owner workspace runtime is the only canonical truth holder for:

- graph truth
- database truth
- canonical case state
- canonical provenance binding

## Edge Boundary

Subordinate edge runtimes can contribute:

- governed observation
- local delegated outcomes
- evidence candidates
- operational runtime state

They cannot hold autonomous canonical truth.

Edge-local spool, retries, snapshots and local outcomes remain operational
state until owner-side canonicalization.

## Final Adjudication Rule

Final adjudication is owner-side only. Canonicalization requires owner runtime
acceptance and persistence.

## References

- `docs/architecture/runtime-model.md`
- `docs/architecture/canonical-data-plane-model.md`
- `docs/architecture/global-to-edge-policy-hierarchy-model.md`
- `docs/architecture/delegated-edge-enforcement-model.md`
