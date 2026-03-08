# yai repository scope

## Role

`yai` is the runtime implementation repository and law consumer.

## In scope

- runtime ingress, lifecycle, dispatch, and enforcement realization
- internal runtime module composition (`core`, `exec`, `brain`)
- runtime consumption/integration of canonical law surfaces

## Out of scope (this tranche)

- canonical law authorship (owned by `law`)
- ops official qualification/collateral publishing (owned by `ops`)
- dataplane/db/query implementation work

## Dependency boundary

`ops` is never a normative source for runtime behavior.
Normative authority comes from `law`.
