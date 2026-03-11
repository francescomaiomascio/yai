# B12 Legacy Sync and Tooling Elimination

Status: completed
Date: 2026-03-11

Implemented:
- Removed active tool/runtime assumptions for `embedded/law`, `../law`, and `YAI_LAW_*` in canonical wrappers.
- Replaced legacy resolver usage with `tools/dev/resolve-governance-root.sh`.
- Removed `tools/dev/resolve-law-compat.sh` and `tools/dev/resolve-law-embed.sh`.
- Switched build and verify flows to canonical governance checks (`yai-governance-compat-check`).
- Kept legacy wrapper names only as explicit deprecation aliases that do not define canonical flow.
- Added tooling guardrail validator: `tools/validate/validate_no_legacy_tooling_references.py`.

Operational rule:
- Canonical toolchain is governance-rooted and single-repo only.
