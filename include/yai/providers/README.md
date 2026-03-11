# Providers Public Headers

Canonical provider infrastructure headers for:

- registry
- inference
- embedding
- mocks

Providers are controlled internal infrastructure of the runtime-governed system,
not a standalone external decision layer.

Canonical headers:

- `providers.h`
- `registry.h`
- `inference.h`
- `embedding.h`
- `mocks.h`

Boundary contract:

- provider APIs expose controlled infrastructure surfaces only
- orchestration/agent planning remains outside this domain
