---
id: workspace-verticalization-gap-classification-v0.1.0
status: active
owner: runtime-governance
updated: 2026-03-10
related:
  - docs/program/reports/workspace-verticalization-manual-execution-report-v0.1.0.md
  - docs/program/reports/workspace-verticalization-hardening-backlog-v0.1.0.md
---

# WSV-7 Gap Classification Matrix (v0.1.0)

## Classification summary

| Bucket | Commands impacted | Severity signal | Notes |
| --- | ---:| --- | --- |
| Runtime implementation missing/incomplete | 0 | n/a | No parser-level unknown-command failures observed. |
| CLI grammar / parser issue | 0 | n/a | Grammar accepted all attempted family commands. |
| CLI help / discoverability issue | 0 | n/a | `help ws` and nested families visible. |
| CLI routing / dispatch issue | 0 confirmed | medium | Could not validate deep routing behavior due upstream runtime unavailability. |
| Runtime command mapping issue | 55 (blocked) | high | All family calls failed with same upstream `SERVER_UNAVAILABLE`. |
| Workspace binding/state issue | 8 lifecycle + 55 downstream | **critical** | Workspace selection/binding could not be established because runtime endpoint unavailable. |
| Graph materialization / query issue | blocked | high | Commands reachable, behavior not validated due no active runtime. |
| DB/store/read-path issue | blocked + artifact checks failed | high | No workspace data root created in this run. |
| Data-plane persistence issue | blocked | high | Could not observe record/evidence persistence in this run. |
| Knowledge surface issue | blocked | medium | Same runtime gate. |
| Policy resolution/effective stack issue | blocked | high | Policy commands never reached live evaluation path. |
| Recovery surface issue | blocked | medium | `ws recovery *` reachable but runtime unavailable. |
| Debug surface issue | blocked | medium | `ws debug resolution` returned `SERVER_UNAVAILABLE`. |
| Law registry drift | 0 in representative checks | low | `workspace_verticalization_closeout_wsv6_v1.sh` law checks passed. |
| SDK surface drift | 0 structural, 1 transient run anomaly | medium | Typed surface present; one transient `sdk_smoke` failure during wave script; standalone rerun green. |
| Docs/manual pack mismatch | 0 | low | Pack commands matched implemented CLI grammar. |
| Compatibility alias confusion | 0 in this run | low | No alias path required for tested commands. |

## Root-cause grouping

### Group G1: Runtime endpoint availability gate
- Primary symptom: `SERVER_UNAVAILABLE` (`rc=40`) across lifecycle/family commands.
- Impact: blocks nearly all functional validation of workspace-rich surfaces.
- Classification buckets hit:
  - runtime command mapping issue (effective)
  - workspace binding/state issue
  - graph/db/data/knowledge/policy/recovery/debug blocked downstream.

### Group G2: Artifact validation blocked by workspace creation failure
- Primary symptom: missing `~/.yai/run/data/<ws>` and graph/event artifacts.
- Impact: cannot verify db/graph persistence reality in this run.
- Buckets hit:
  - db/store/read-path
  - data-plane persistence
  - graph materialization/read.

### Group G3: SDK wave-script instability (non-deterministic)
- Primary symptom: one scripted `sdk make test` run failed (`sdk_smoke: context set failed`), direct rerun passed.
- Impact: introduces uncertainty in strict scripted sequencing.
- Buckets hit:
  - sdk surface drift (execution stability, not API shape).

## PASS/FAIL applicability by command class

- `PASS`: syntax/discoverability (help + command recognition).
- `FAIL`: runtime-backed behavior classes, due environment/runtime availability gate.
- `NOT EXECUTED`: none.
- `BLOCKED BY PRIOR FAILURE`: logically many, but commands were still attempted and classified explicitly as fail.
