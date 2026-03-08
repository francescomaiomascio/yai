# Dependencies Boundary Notes

## `deps/law`

Status: `bridge`  
Primary usage: `disabled by default`  
Role: legacy compatibility fallback only

Canonical and active paths:

- Canonical source of truth: sibling repo `../law`
- Runtime-consumed surface: `embedded/law`

`deps/law` must not be treated as primary normative source in active runtime flow.
Enable bridge fallback only when explicitly required (`YAI_LAW_ENABLE_LEGACY_BRIDGE=1`).
