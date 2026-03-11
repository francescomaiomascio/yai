# Providers Implementation Domain (Canonical)

`lib/providers/` is controlled provider infrastructure for the unified YAI
system.

Canonical subdomains:

- `registry/`
- `embedding/`
- `inference/`
- `mocks/`
- `internal/`

Domain responsibility:

- registry: provider identity, capabilities, and compatibility/trust gating
- embedding: vector-generation services for indexing/retrieval support
- inference: completion/decision execution surfaces
- mocks: deterministic providers for tests and qualification

Boundary rules:

- `providers/` is internal infrastructure, not orchestration.
- `providers/` does not define agent behavior.
- `providers/` does not own governance policy resolution.
