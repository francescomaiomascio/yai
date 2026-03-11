# B10 Embedded Removal Execution

Status: completed
Date: 2026-03-11

Actions executed:
- Removed `embedded/law` from active repository topology.
- Removed runtime/tooling fallback path usage for `embedded/law`.
- Cut over workspace/governance session helpers to canonical governance path resolution only.
- Replaced legacy make/test targets (`law-embed-sync`, `law-embed-check`) with canonical governance targets.
- Updated manifest publish target naming from `runtime-embedded` to `runtime-governance`.

Remaining legacy:
- Transitional notes may still mention `embedded/law` as historical context only.
- Legacy wrapper names (`yai-law-embed-sync`, `yai-law-sync`, `yai-specs-sync`) now hard-fail and are not supported.
