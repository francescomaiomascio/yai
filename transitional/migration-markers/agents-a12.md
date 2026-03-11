# A12 Migration Marker - Agents Mechanical Placement

Canonical agent implementation now lives under `lib/agents/`.

Compatibility note:

- `include/yai/exec/agents.h` remains a transitional shim.

Boundary lock:

- avoid introducing new conceptual orchestration control under `lib/agents/`.
- agent logic remains subordinate to orchestration and runtime governance.
