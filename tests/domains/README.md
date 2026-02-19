# Domain Test Layout

Goal: keep tests small and component-focused before scaling.

Domains:

- `boot/`: bootstrap and preboot invariants
- `kernel/`: core protocol/runtime invariants in kernel boundary
- `root/`: control transport and root boundary behavior
- `engine/`: engine cortex/gates/bridge behavior

Shared:

- place reusable helpers/fixtures under `tests/shared`
