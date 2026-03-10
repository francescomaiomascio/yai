# Tests

Authoritative test topology:

- `tests/unit/core`
- `tests/unit/exec`
- `tests/unit/brain` (legacy directory name; coverage maps to `knowledge/graph/exec` split)
- `tests/unit/protocol`
- `tests/unit/support`
- `tests/integration/runtime_handshake`
- `tests/integration/workspace_lifecycle`
- `tests/integration/core_exec`
- `tests/integration/core_brain` (legacy integration label retained for compatibility)
- `tests/e2e`
- `tests/fixtures`
- `tests/shared`

Legacy taxonomy:

- `tests/domains/*` is deprecated and retained temporarily as compatibility marker only.

Primary commands:

- `make test-unit`
- `make test-integration`
- `make test-demo-matrix`
- `make test-e2e`
- `make test`
- `tests/integration/workspace_lifecycle/workspace_verticalization_closeout_wsv6_v1.sh` (cross-repo representative WSV-6 closeout check)
- `tests/integration/workspace_lifecycle/workspace_runtime_reachability_convergence_wsv81_v1.sh` (WSV-8.1 runtime/control-plane convergence check)
- `tests/integration/workspace_lifecycle/workspace_binding_postconditions_wsv82_v1.sh` (WSV-8.2 workspace bind/persistence/artifact post-condition check)
