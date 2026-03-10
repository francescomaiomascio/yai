---
id: workspace-verticalization-evidence-index-v0.1.0
status: active
owner: runtime-governance
updated: 2026-03-10
related:
  - docs/program/reports/workspace-verticalization-manual-execution-report-v0.1.0.md
---

# WSV-7 Evidence Index (v0.1.0)

## Raw evidence bundle

- Root: `/tmp/wsv7_manual_execution_20260310_192614`
- Summary log: `/tmp/wsv7_manual_execution_20260310_192614/summary.log`
- RC files: `/tmp/wsv7_manual_execution_20260310_192614/*.rc`
- Output files: `/tmp/wsv7_manual_execution_20260310_192614/*.out`

## Key evidence pointers

- CLI ws taxonomy:
  - `/tmp/wsv7_manual_execution_20260310_192614/pre_02.out`
- Lifecycle readiness mismatch:
  - `/tmp/wsv7_manual_execution_20260310_192614/lc_01.out`
- Representative family failures (`SERVER_UNAVAILABLE`):
  - `/tmp/wsv7_manual_execution_20260310_192614/gr_summary.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/db_status.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/dt_evidence.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/kn_status.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/pol_04.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/rcv_01.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/dbg_01.out`
- Artifact absence checks:
  - `/tmp/wsv7_manual_execution_20260310_192614/ev_01.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/ev_02.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/ev_03.out`
- SDK and cross-repo checks:
  - `/tmp/wsv7_manual_execution_20260310_192614/sdk_01.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/sdk_02.out`
  - `/tmp/wsv7_manual_execution_20260310_192614/law_01.out`

## Supplemental diagnostics captured outside bundle

- `cli` runtime doctor snapshot:
  - `yai doctor runtime` (captured in session transcript)
- `cli` runtime inspect snapshot:
  - `yai inspect runtime` (captured in session transcript)
- `cli` verbose contract snapshot:
  - `yai --verbose-contract runtime ping` (captured in session transcript)
- `sdk` consistency rerun:
  - `cd /Users/francescomaiomascio/Developer/YAI/sdk && make test` -> PASS (captured in session transcript)
