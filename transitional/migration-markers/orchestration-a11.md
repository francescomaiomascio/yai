# A11 Migration Marker - Orchestration Canonicalization

Canonical orchestration implementation now lives under `lib/orchestration/`.

Compatibility note:

- `include/yai/exec/orchestration.h` remains transitional shim during
  convergence.

Boundary lock:

- new orchestration semantics should not be introduced under
  `lib/exec/orchestration/`.
