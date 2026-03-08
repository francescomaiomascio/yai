# Law Consumption Model

## Contract boundary

- Canonical normative source: `law` repository.
- Runtime contract artifact: `embedded/law/`.
- Legacy bridge: `deps/law/` fallback-only.

## Active six-layer consumption

`yai` consumes embedded payloads by layer:
- `classification/`
- `control-families/`
- `domain-specializations/`
- `overlays/regulatory/`
- `overlays/sector/`
- `overlays/contextual/`

Runtime loaders validate layer indexes and generated summaries before resolution.

## Bridge policy

`deps/law` remains allowed only when embedded contract payload is unavailable.
It is not the primary path and must not be expanded.
Fallback bridge loading is disabled by default and requires `YAI_LAW_ENABLE_LEGACY_BRIDGE=1`.

## Surface classes

- `active runtime-facing`: `embedded/law`
- `canonical source`: sibling `law` repository
- `bridge`: `deps/law` (explicit opt-in only)
- `historical/reference-only`: legacy debug/report docs
