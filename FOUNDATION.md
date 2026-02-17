# Foundation

YAI is a sovereign runtime: authority is explicit, execution is deterministic, and effects are traceable.
The system is designed so contracts define behavior and runtime enforces behavior without silent drift.

## Layer Model

- `L0 Contracts` - canonical normative contracts in `deps/yai-specs/`
- `L1 Kernel` - authority enforcement, boundary checks, and policy gating
- `L2 Engine` - deterministic execution under kernel-governed constraints
- `L3 Mind/Clients` - proposers/orchestrators that never override authority

## Non-Negotiable Principles

- Auditability: externally relevant actions must be reconstructible from logs/events.
- No silent side effects: state/effect changes require explicit command path and policy checks.
- Effect boundary: authority boundaries are explicit and enforced at runtime interfaces.
- Spec-first: runtime contracts are implemented from `deps/yai-specs`; implementation is never normative.

## Runtime Guarantees

- Authority decisions are made in governed planes, not inferred ad hoc.
- Workspace isolation is first-class and enforced across socket/process boundaries.
- Deterministic components remain deterministic even when integrated with probabilistic clients.

## License

Foundation and governance artifacts in this repository are distributed under Apache-2.0.
