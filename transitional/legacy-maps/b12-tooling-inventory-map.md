# B12 Tooling Inventory Map

Date: 2026-03-11

## A. Eliminated/retired from canonical flow
- `tools/dev/resolve-law-compat.sh` (removed)
- `tools/dev/resolve-law-embed.sh` (removed)

## B. Refounded to canonical governance root
- `tools/bin/yai-check-pins`
- `tools/bin/yai-proof-check`
- `tools/bin/yai-verify`
- `tools/bin/yai-docs-trace-check`
- `tools/bin/yai-gate`
- `tools/bin/yai-changelog-check`
- `tools/bin/yai-bundle`
- `tools/bin/yai-suite`
- `tools/dev/check-generated.sh`
- `tools/dev/verify_final_demo_matrix.sh`
- `tests/unit/protocol/run_protocol_unit_tests.sh`
- `tests/unit/knowledge/run_knowledge_unit_tests.sh`
- `tests/integration/workspace/workspace_binding_postconditions_wsv82_v1.sh`
- `tests/integration/workspace/workspace_runtime_reachability_convergence_wsv81_v1.sh`

## C. Legacy aliases confined/declassified
- `tools/bin/yai-law-sync` (hard-fail)
- `tools/bin/yai-specs-sync` (hard-fail)
- `tools/bin/yai-law-embed-sync` (hard-fail)
- `tools/bin/yai-law-compat-check` (deprecated alias to `yai-governance-compat-check`)
