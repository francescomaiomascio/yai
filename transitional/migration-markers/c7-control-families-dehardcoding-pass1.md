# C7 — Control Families De-Hardcoding Pass I

State:
- Canonical model moved to descriptor/index surfaces under `governance/families/`.
- Runtime/loader now supports index-driven control-family descriptor loading.

Primary semantic surfaces:
- `families/index/families.descriptors.index.json`
- `families/index/family.matrix.v1.json`
- `families/descriptors/*.descriptor.v1.json`
- `families/schema/*.v1.schema.json`

Compatibility:
- Per-family `families/<family>/manifest.json` remains materialized and secondary.
- `manifest_ref` stays present in `families.index.json` for transitional consumers.
