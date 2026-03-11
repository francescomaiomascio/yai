# Graph Implementation Domain (Canonical)

`lib/graph/` is the first-class relational materialization and read surface for
runtime-governed state.

Canonical subdomains:

- `materialization/`
- `query/`
- `state/`
- `domains/`
- `internal/`

Boundary rules:

- `graph/` materializes and reads relations.
- `graph/` consumes `data/` records/evidence as source plane.
- `graph/` does not replace data-plane persistence.
