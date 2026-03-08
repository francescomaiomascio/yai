# Law Consumption Model

## Canonical separation

- `law` is the canonical normative source and remains an independent repository.
- `yai` is a runtime consumer and must not depend on full live traversal of the law repo tree.

## Consumption boundary

`yai` consumes exported runtime-facing material from `embedded/law/`.
This surface is generated from law export manifests and includes only runtime-consumable sections.

Primary consumed sections:
- law/runtime manifests
- domains (runtime-facing shape)
- compliance packs (runtime-facing shape)
- generated indexes and compatibility summaries

Excluded by design:
- full authority/foundation prose
- historical/refactor archives
- non-runtime-facing formal/tooling material

## Transitional fallback

`deps/law/` is retained as a transition bridge.
It is not the target model and must not grow as a primary normative dependency surface.

## Operational flow

1. Sync embedded law from canonical `law` via `tools/bin/yai-law-embed-sync`.
2. Validate local embedded compatibility with `tools/bin/yai-law-compat-check`.
3. Runtime law consumer reads `embedded/law` as primary ingress.
