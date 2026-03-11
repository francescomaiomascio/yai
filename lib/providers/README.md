# Providers Implementation Domain (Canonical)

`lib/providers/` is controlled provider infrastructure for the unified YAI
system.

Canonical subdomains:

- `registry/`
- `embedding/`
- `inference/`
- `selection/`
- `policy/`
- `mocks/`
- `internal/`

Domain responsibility:

- registry: provider identity, descriptors, capability metadata
- embedding: embedding adapters and invocation surfaces
- inference: inference adapters and invocation surfaces
- selection: runtime provider routing and fallback resolution
- policy: trust/admissibility gating used by selection
- mocks: deterministic providers for tests and qualification

Boundary rules:

- `providers/` is internal infrastructure, not orchestration.
- `providers/` does not define agent behavior.
- `providers/` does not own governance policy resolution.
- protocol-level contracts and wire schemas stay under `protocol/`.
