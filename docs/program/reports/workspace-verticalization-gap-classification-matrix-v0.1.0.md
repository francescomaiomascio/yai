---
id: workspace-verticalization-gap-classification-matrix-v0.1.0
status: active
owner: runtime-governance
updated: 2026-03-10
related:
  - docs/program/reports/workspace-verticalization-gap-audit-v0.1.0.md
  - docs/program/reports/workspace-verticalization-wsv8-closure-plan-v0.1.0.md
---

# WSV-7.5 Gap Classification Matrix (v0.1.0)

## Matrix

| Gap cluster | Result type | Root cause class | Affected commands/families (collapsed) | Repo ownership | Severity | Fix mode | WSV-8 package |
| --- | --- | --- | --- | --- | --- | --- | --- |
| G-01 Runtime endpoint unavailable after lifecycle up | `FAIL` | runtime mapping + workspace binding/state issue | `lifecycle up`, `ws create/open/set/switch/current/status/inspect`, all family subcommands returning `SERVER_UNAVAILABLE` | yai + yai-cli | `S1` | direct implementation + output contract stabilization | WP-1 |
| G-02 Workspace artifacts not materialized | `FAIL` | db/store/read-path + data-plane persistence + graph materialization | artifact checks `ev_01..ev_05`; no workspace data root / graph/events files | yai | `S1` | direct implementation + post-condition verification | WP-2 |
| G-03 Lifecycle/doctor/inspect readiness narrative mismatch | `PASS WITH DEBT` | runtime output contract drift | lifecycle says reachable/not-ready while doctor+inspect show unreachable/unavailable | yai-cli (+ yai runtime surfaces) | `S2` | output contract stabilization | WP-3 |
| G-04 Family execution blocked uniformly (graph/db/data/knowledge/policy/domain/recovery/debug/query) | `FAIL` | runtime mapping gate + family preflight diagnostics gap | `ws graph *`, `ws db *`, `ws data *`, `ws knowledge *`, `ws policy *`, `ws domain *`, `ws recovery *`, `ws debug resolution`, `ws query *` | yai + yai-cli | `S2` | mapping correction + diagnostics improvements | WP-4 |
| G-05 SDK scripted smoke non-determinism | `FRAGILE PASS` | sdk drift (test harness sequencing) | one wave-script `sdk make test` failed (`sdk_smoke context set`), standalone rerun green | yai-sdk | `S3` | test/guardrail addition + harness hardening | WP-5 |
| G-06 Composition-backed ws-db/ws-recovery/ws-knowledge subpaths | `PASS WITH DEBT` | runtime implementation incomplete (direct-id depth) | `ws db bindings/stores/classes/count`, `ws recovery status/load/reopen`, parts of `ws knowledge` | yai + yai-cli + yai-sdk + yai-law | `S3` | mapping correction + phased direct implementation | WP-6 |
| G-07 Compatibility/fallback exposure noise | `COMPATIBILITY NOISE` | compatibility alias / fallback positioning | fallback query and compatibility paths remain visible in advanced usage | yai-cli + yai-sdk | `S4` | surface cleanup + docs/help correction | WP-7 |
| G-08 No doc/help drift on canonical ws family tree | `DOC/HELP DRIFT` (none detected) | n/a | `help ws` and nested topics aligned | yai-cli + yai docs | `S4` (monitor) | guardrail retention | WP-7 |

## Severity and ownership rollup

Severity totals:
- `S1`: 2 clusters
- `S2`: 2 clusters
- `S3`: 2 clusters
- `S4`: 2 clusters (1 noise + 1 monitor)

Ownership totals (primary):
- `yai`: 4 clusters
- `yai-cli`: 4 clusters
- `yai-sdk`: 2 clusters
- `yai-law`: 1 cluster (composition/mapping parity monitor)
- cross-repo: 2 clusters

## Notes on structural collapsing

The matrix intentionally collapses duplicate failures:
- 55 `SERVER_UNAVAILABLE` command failures are treated as one `S1` runtime-availability cluster plus one `S2` family-diagnostics cluster, not 55 independent bugs.
- Artifact absence is treated as one persistence/materialization cluster (`S1`), not five separate file-check failures.
