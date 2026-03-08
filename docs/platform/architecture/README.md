# Platform Architecture

This section documents runtime architecture.

Normative source model:
- Canonical normative repository: `law`
- Runtime artifact consumed by `yai`: `embedded/law`
- Legacy transition bridge: `deps/law` (fallback only, opt-in via `YAI_LAW_ENABLE_LEGACY_BRIDGE=1`)

Historical references to old law mirror paths are compatibility-only and not primary runtime references.
