# A5 Migration Marker - Law to Governance Naming

Status: active transitional marker.

Canonical naming:

- `governance`

Legacy naming (compatibility only):

- `law`

Transitional compatibility surfaces:

- `include/yai/law/` (header shims)
- `lib/law/` (legacy marker only)
- `embedded/law/` (migration-only artifact root)

Exit criteria:

1. Runtime loader no longer depends on `embedded/law`.
2. Build/test aliases no longer need `law-*` target names.
3. External `../law` references are replaced by internal `governance/` paths or archived.
