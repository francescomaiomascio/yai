# Transitional Area (Migration-Only)

This directory is migration-only.

Purpose:

- keep temporary markers while converging runtime + governance into one repo
- host compatibility shims that must be removed after cutover
- isolate legacy layout references from final canonical tree

Rules:

- no net-new canonical features must be developed under `transitional/`
- every transitional artifact must have an explicit removal/cutover target
- final-state content belongs in canonical roots (`governance/`, `docs/`,
  `include/`, `lib/`, `tests/`, `tools/`)
