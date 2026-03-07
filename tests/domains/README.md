# Legacy Domain Test Layout (Deprecated)

`tests/domains/*` is retained only as a temporary compatibility marker.
New and migrated tests must use:

- `tests/unit/{core,exec,brain,protocol,support}`
- `tests/integration/{runtime_handshake,workspace_lifecycle,core_exec,core_brain}`
- `tests/e2e`

Legacy domain buckets are scheduled for removal after the final decommission pass.
