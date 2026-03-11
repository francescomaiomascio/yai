# A13 - Providers and Knowledge Alignment

A13 aligns providers and knowledge as distinct internal infrastructure domains
of the unified YAI architecture.

## Canonical providers topology

- `lib/providers/registry/`
- `lib/providers/embedding/`
- `lib/providers/inference/`
- `lib/providers/mocks/`
- `lib/providers/internal/`

## Canonical knowledge topology

- `lib/knowledge/cognition/`
- `lib/knowledge/memory/`
- `lib/knowledge/semantic/`
- `lib/knowledge/episodic/`
- `lib/knowledge/vector/`
- `lib/knowledge/internal/`

## A13 cutover actions

- moved provider implementation out of `lib/knowledge/providers/` into
  canonical `lib/providers/` subdomains.
- separated knowledge semantic/vector implementation out of memory internals.
- promoted `include/yai/providers/*` as canonical provider header surface.
- retained `include/yai/knowledge/providers.h` as compatibility shim.

## Boundary model

- providers: controlled external-model infrastructure (registry/inference/
  embedding/mocks).
- knowledge: cognition/memory/retrieval internals.
- graph, agents, and orchestration consume these services but do not redefine
  their domain boundaries.
