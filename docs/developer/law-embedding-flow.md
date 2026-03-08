# Law Embedding Flow

## Source policy

- Author in canonical `law`.
- Export runtime contract from `law`.
- Consume in `yai/embedded/law`.

## Commands

```bash
./tools/bin/yai-law-embed-sync
./tools/bin/yai-law-compat-check
```

## Resolution order

1. `embedded/law` (primary)
2. `deps/law` (fallback bridge only, if `YAI_LAW_ENABLE_LEGACY_BRIDGE=1`)

## Rule

Do not author normative payload directly in `embedded/law`.
Treat legacy and historical docs as secondary context only; runtime contract source is embedded payload plus canonical `law` manifests.
