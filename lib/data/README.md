# Data Implementation Domain (Canonical)

`lib/data/` is the first-class persistence, records, and evidence plane for
the unified YAI runtime.

Canonical subdomains:

- `records/`
- `query/`
- `binding/`
- `lifecycle/`
- `store/`
- `evidence/`
- `retention/`
- `internal/`

Boundary rules:

- `data/` owns record and evidence persistence.
- `graph/` consumes data-plane records to materialize operational views.
