# A13 Migration Marker - Providers and Knowledge Alignment

Canonical provider implementation now lives under `lib/providers/`.

Compatibility note:

- `include/yai/knowledge/providers.h` remains transitional shim to
  `include/yai/providers/providers.h`.

Boundary lock:

- no new provider implementation should be reintroduced under
  `lib/knowledge/providers/`.
