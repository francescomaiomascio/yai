# Runtime Model

`yai` is the runtime host of the platform and executes the internal modules `core`, `exec`, and `brain`.

## Canonical runtime flow

1. Ingress request reaches runtime control surface.
2. Runtime builds classification context from the operation.
3. Embedded law is loaded and validated.
4. Domain discovery selects applicable domain policy context.
5. Normative stack is resolved (foundation -> domain -> compliance -> overlays hook).
6. Final effect is handed to enforcement.
7. Decision/evidence trace shape is returned for downstream handling.

## Repository boundaries

- Normative source of truth is in sibling repo `law`.
- `yai` consumes the runtime-facing export under `embedded/law/`.
- `ops` is qualification/publication bureau and not runtime normative authority.

## Scope note

Dataplane persistence/query is outside this tranche.
This runtime model ends at decision/evidence envelope preparation and enforcement handoff.
