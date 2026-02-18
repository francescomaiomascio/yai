# Tooling Layout Migration

Repository: `yai`
Goal: remove legacy `scripts` tree and make `tools` + `tests` canonical.

## Tooling Table

| PATH | CLASS | NOTES |
|---|---|---|
| tools/bin/yai-doctor | entrypoint | user-facing command |
| tools/bin/yai-purge | entrypoint | user-facing command |
| tools/bin/yai-verify | entrypoint | user-facing command |
| tools/bin/yai-gate | entrypoint | user-facing command |
| tools/bin/yai-suite | entrypoint | user-facing command |
| tools/ops/gate/gate.sh | ops | operator wrapper |
| tools/ops/suite/suite.sh | ops | operator wrapper |
| tools/ops/verify/verify.sh | ops | operator wrapper |
| tools/ops/gate/cortex.sh | ops | gate implementation |
| tools/ops/gate/dataset-global-stress.sh | ops | gate implementation |
| tools/ops/gate/events.sh | ops | gate implementation |
| tools/ops/gate/graph.sh | ops | gate implementation |
| tools/ops/gate/providers.sh | ops | gate implementation |
| tools/ops/gate/providers-modes-test.sh | test | deterministic pass/fail gate test |
| tools/ops/gate/ws.sh | ops | gate implementation |
| tools/ops/gate-cortex.sh | ops | wrapper retained by name |
| tools/ops/gate-dataset-global-stress.sh | ops | wrapper retained by name |
| tools/ops/gate-graph.sh | ops | wrapper retained by name |
| tools/ops/gate-providers.sh | ops | wrapper retained by name |
| tools/ops/gate-ws.sh | ops | wrapper retained by name |
| tools/ops/suite/levels/l0-l7.sh | ops | suite implementation |
| tools/ops/suite/ops/no-llm-360.sh | ops | suite implementation |
| tools/ops/suite/ops/fault-injection-v1.sh | ops | suite implementation |
| tools/ops/suite/ops/perf-slo-v1.sh | ops | suite implementation |
| tools/ops/suite/ops/recovery-compat-v1.sh | ops | suite implementation |
| tools/ops/suite/ops/security-sanity-v1.sh | ops | suite implementation |
| tools/ops/suite/ops/stress-v1.sh | ops | suite implementation |
| tools/ops/suite-l0-l7.sh | ops | top-level wrapper retained by name |
| tools/ops/suite-ops-360-no-llm.sh | ops | top-level wrapper retained by name |
| tools/ops/verify/core.sh | ops | verify implementation |
| tools/ops/verify/law-kernel.sh | ops | verify implementation |
| tools/ops/verify-core.sh | ops | wrapper retained by name |
| tools/ops/verify-events.sh | ops | wrapper retained by name |
| tools/ops/verify-law-kernel.sh | ops | wrapper retained by name |
| tools/dev/check-generated.sh | dev | duplicate wrapper removed |
| tools/dev/resolve-yai-bin.sh | dev | shared helper |
| tools/dev/protocol_tester | dev | duplicate wrapper removed |
| tools/dev/gen-vault-abi | dev | duplicate wrapper removed |
| tools/dev/yai-doctor | dev | internal impl used by entrypoint |
| tools/dev/yai-purge | dev | internal impl used by entrypoint |
| tools/release/bump_version.sh | release | release tool |
| tools/release/check_pins.sh | release | release tool |
| tools/release/pin_cli.sh | release | release tool |
| tools/data/fetch-embeddings.sh | data | canonical copy |
| tools/data/dataset-global-stress.sh | data | data gate wrapper |
| tools/data/global-stress/v1/import-seed-via-cli.sh | data | tooling moved out of data |
| tools/data/global-stress/v1/load-events-log.sh | data | tooling moved out of data |
| tools/data/global-stress/v1/README.md | data | updated tooling location |
| tests/integration/test_handshake.py | test | duplicate consolidated |
| tools/bundle/build_bundle.sh | dev | bundling helper |
| tools/bundle/manifest.sh | dev | bundling helper |
| tools/bundle/README.md | dev | bundling helper docs |
| tools/README.md | dev | canonical layout docs |
| tools/lib/logging.sh | dev | shared helper |
| tools/ops/fault-injection-v1.sh | ops | wrapper retained by name |
| tools/ops/perf-slo-v1.sh | ops | wrapper retained by name |
| tools/ops/recovery-compat-v1.sh | ops | wrapper retained by name |
| tools/ops/security-sanity-v1.sh | ops | wrapper retained by name |
| tools/ops/stress-v1.sh | ops | wrapper retained by name |
## Verification

Date: 2026-02-18

- `make clean && make`: PASS
- `tools/bin/yai-verify --help`: exits with `FAIL: unknown verify '--help'` and lists checks (expected current CLI behavior)
- `tools/bin/yai-suite --help`: exits with `FAIL: unknown suite '--help'` and lists suites (expected current CLI behavior)
- `tools/bin/yai-gate --help`: exits with `FAIL: unknown gate '--help'` and lists gates (expected current CLI behavior)
- `tools/bin/yai-doctor --help`: executable runs diagnostics and completes
- `tools/bin/yai-purge --help`: no dedicated help flag; executes purge flow
- `find . -type d -name scripts`: no output (zero directories)
- `rg -n "scripts slash pattern" -S .`: no output for legacy script-path references
- `tree -a tools | head -n 200`: canonical layout present (`bin`, `ops`, `dev`, `release`, `data`, `bundle`, `lib`)
