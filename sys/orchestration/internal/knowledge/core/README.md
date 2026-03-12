# Knowledge Implementation Domain (Canonical)

`lib/knowledge/` is governed internal cognition/memory infrastructure.

Canonical subdomains:

- `cognition/`
- `memory/`
- `semantic/`
- `episodic/`
- `vector/`
- `internal/`

Domain responsibility:

- cognition: reasoning roles, scoring, synthesis, controlled cognitive flow
- memory: persistence model, storage bridge, retrieval interfaces
- semantic: structured meaning layer
- episodic: event-history and experience memory
- vector: vector indexing and nearest-neighbor retrieval

Boundary rules:

- `knowledge/` is not `graph/` state materialization.
- `knowledge/` is not `agents/` role orchestration.
- `knowledge/` is runtime-governed infrastructure, not an external AI subsystem.
