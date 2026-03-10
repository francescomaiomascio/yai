---
id: workspace-verticalization-manual-execution-report-v0.1.0
status: active
owner: runtime-governance
updated: 2026-03-10
scope: [yai, yai-law, yai-cli, yai-sdk]
related:
  - docs/program/audit-convergence/WORKSPACE-VERTICALIZATION-MANUAL-TEST-COMMAND-PACK-v0.1.0.md
  - docs/program/audit-convergence/WORKSPACE-VERTICALIZATION-ECOSYSTEM-VERIFICATION-MATRIX-v0.1.0.md
  - docs/program/reports/workspace-verticalization-gap-classification-v0.1.0.md
  - docs/program/reports/workspace-verticalization-hardening-backlog-v0.1.0.md
---

# WSV-7 Manual Execution Report (v0.1.0)

## Execution baseline

- Date: 2026-03-10
- Runner: manual command-pack wave execution
- Evidence root: `/tmp/wsv7_manual_execution_20260310_192614`
- Command source: `WORKSPACE-VERTICALIZATION-MANUAL-TEST-COMMAND-PACK-v0.1.0`
- Total commands attempted: **67**

## Result classes (global)

- `PASS`: 6
- `PASS WITH DEBT`: 0 (command-level)
- `FAIL`: 61
- `NOT EXECUTED`: 0
- `BLOCKED BY PRIOR FAILURE`: 0

RC distribution:
- `rc=0`: 6
- `rc=40` (`SERVER_UNAVAILABLE`): 55
- `rc=1`: 5
- `rc=2`: 1

## Family-by-family execution summary

| Family | Attempted | PASS | FAIL | Notes |
| --- | ---:| ---:| ---:| --- |
| Prerequisites | 2 | 2 | 0 | `yai --version`, `help ws` green |
| Workspace lifecycle | 9 | 1 | 8 | `ws clear` pass; rest blocked by runtime unavailable |
| Graph | 9 | 0 | 9 | all `rc=40` |
| DB | 6 | 0 | 6 | all `rc=40` |
| Data | 6 | 0 | 6 | all `rc=40` |
| Knowledge | 5 | 0 | 5 | all `rc=40` |
| Policy | 5 | 0 | 5 | all `rc=40` |
| Domain | 2 | 0 | 2 | all `rc=40` |
| Recovery | 3 | 0 | 3 | all `rc=40` |
| Debug | 1 | 0 | 1 | `rc=40` |
| Query fallback | 9 | 0 | 9 | all `rc=40` |
| Artifact checks | 5 | 0 | 5 | workspace files absent because workspace creation blocked |
| SDK checks | 2 | 1 | 1 | `example_04` pass (graceful server_off), one `make test` run failed transiently |
| Law cross-check | 1 | 1 | 0 | WSV-6 closeout script pass |
| Teardown | 2 | 1 | 1 | `ws unset` blocked (`rc=40`), `lifecycle down` pass |

## Key evidence excerpts

1. CLI surface exists and is rich:
   - `pre_02.out` shows canonical `ws` families: `graph`, `db`, `data`, `knowledge`, `policy`, `domain`, `recovery`, `debug`, `query`.

2. Runtime liveness/readiness mismatch at execution time:
   - `lc_01.out`: `Runtime liveness reachable`, `Runtime readiness not ready`.
   - `doctor runtime` and `inspect runtime`: `Liveness unreachable`, `Readiness unavailable`.
   - `--verbose-contract runtime ping`: `code=SERVER_UNAVAILABLE`, `reason=server_unavailable`.

3. Family command attempts are wired but blocked:
   - graph/db/data/knowledge/policy/domain/recovery/debug/fallback command outputs consistently return `SERVER UNAVAILABLE`.

4. Artifact evidence unavailable:
   - `ev_01.out`..`ev_05.out`: no workspace directories/files created because `ws create`/`ws set` failed under unavailable runtime.

5. SDK consistency:
   - During wave script one run failed (`sdk_smoke: context set failed`).
   - Re-run outside wave script passed fully: `cd /Users/francescomaiomascio/Developer/YAI/sdk && make test` -> green.

## Evidence integrity statement

This report is based on real command execution, not inferred state.
Raw outputs are stored under `/tmp/wsv7_manual_execution_20260310_192614/*.out` with per-command return codes in `*.rc`.

## Updated readiness disposition

**NOT OPERATOR READY** (for full manual workspace wave in tested environment).

Reason:
- canonical surface is present and discoverable,
- but runtime endpoint availability blocked end-to-end family execution (`55/67` commands failed with `SERVER_UNAVAILABLE`),
- so graph/db/data/knowledge/policy/recovery inspectability could not be validated under live bound workspace conditions in this run.
