# Foundation

YAI is a sovereign governed runtime system: authority is explicit, execution is deterministic, and effects are traceable.

This repository is being refounded as the canonical root of the final unified system.

## Layer Model

- **L0 — Governance Contracts**: canonical governance/model content in `governance/` (target canonical root)
- **L1 — Kernel**: authority enforcement, boundary checks, and policy gating
- **L2 — Engine**: deterministic execution under kernel-governed constraints
- **L3 — Mind / Clients**: proposers and orchestrators that never override authority

## Non-Negotiable Principles

- **Auditability**: externally relevant actions must be reconstructible from logs/events.
- **No silent side effects**: state/effect changes require an explicit command path and policy checks.
- **Effect boundary**: authority boundaries are explicit and enforced at runtime interfaces.
- **Spec-first**: normative behavior is governance-defined; implementation is never normative.
- **Single-root convergence**: runtime, governance, docs, tests, and tooling converge in one repository topology.

## Runtime Guarantees

- Authority decisions are made in governed planes, never inferred ad hoc by clients.
- Workspace isolation is first-class and enforced across process/socket boundaries.
- Deterministic components remain deterministic even when integrated with probabilistic clients.

## Canonical Root Topology

The canonical macro-areas of this repository are:

- `cmd/`
- `governance/`
- `include/`
- `lib/`
- `docs/`
- `tests/`
- `tools/`
- `data/`
- `transitional/` (migration-only)

`embedded/` is transitional legacy and not part of the final canonical target.

## License

Foundation and governance artifacts in this repository are distributed under Apache-2.0.
