---
id: workspace-verticalization-gap-audit-v0.1.0
status: active
owner: runtime-governance
updated: 2026-03-10
scope: [yai, yai-law, yai-cli, yai-sdk]
related:
  - docs/program/reports/workspace-verticalization-manual-execution-report-v0.1.0.md
  - docs/program/reports/workspace-verticalization-gap-classification-matrix-v0.1.0.md
  - docs/program/reports/workspace-verticalization-wsv8-closure-plan-v0.1.0.md
---

# WSV-7.5 Workspace Surface Gap Audit (v0.1.0)

## 1) Executive summary

WSV-7 manual execution produced high-confidence evidence that:
- canonical workspace surface exists and is discoverable (`help ws` is rich and coherent),
- but live operator execution is blocked by a runtime availability gate.

Observed from manual run:
- total commands attempted: `67`
- failed with `SERVER_UNAVAILABLE`: `55`
- non-runtime failures: `6` (`5` artifact absence checks + `1` transient sdk scripted failure)

Severity distribution (structural gaps):
- `S1`: 2
- `S2`: 2
- `S3`: 2
- `S4`: 1

Audit disposition:
- **operator execution currently blocked by infrastructure/runtime readiness gate**, not by ws taxonomy absence.

## 2) Family-by-family audit

### Lifecycle / binding
- Result: `FAIL` (except `ws clear`).
- Structural finding: runtime lifecycle reports partial liveness but endpoint remains unreachable for workspace actions.
- Severity: `S1`.

### Graph
- Result: `FAIL` (all attempts).
- Structural finding: family grammar/routing exists; execution blocked upstream.
- Severity: `S2` (blocked by S1 root cause).

### DB
- Result: `FAIL` (all attempts).
- Structural finding: first-class surface exists; no live workspace-bound store state observed.
- Severity: `S2` (blocked by S1 root cause + composition debt).

### Data
- Result: `FAIL` (all attempts).
- Structural finding: routed calls fail before data-plane evidence can be observed.
- Severity: `S2` (blocked by S1).

### Knowledge
- Result: `FAIL` (all attempts).
- Structural finding: commands accepted; blocked by same upstream gate.
- Severity: `S3`.

### Policy
- Result: `FAIL` (all attempts).
- Structural finding: effective stack path unreachable in run conditions.
- Severity: `S2`.

### Domain
- Result: `FAIL` (all attempts).
- Structural finding: domain get/set path unreachable due runtime endpoint gate.
- Severity: `S3`.

### Recovery
- Result: `FAIL` (all attempts).
- Structural finding: exposed surface exists; runtime gate prevents behavioral verification.
- Severity: `S3`.

### Debug
- Result: `FAIL`.
- Structural finding: debug resolution path exists but unreachable under runtime gate.
- Severity: `S3`.

### Query fallback
- Result: `FAIL` in same pattern (`SERVER_UNAVAILABLE`).
- Structural finding: fallback still operationally blocked by root cause.
- Severity: `S3`.

## 3) Root-cause consolidation

### RC-1 Runtime endpoint availability gate
- Symptom set:
  - `lifecycle up` non-ready status
  - `doctor/inspect runtime` unreachable
  - `runtime ping` -> `SERVER_UNAVAILABLE`
  - all ws families blocked.
- Class: `runtime mapping/availability + workspace binding/state`.
- Severity: `S1`.
- Primary owner: `yai` (runtime), `yai-cli` (readiness semantics/output).

### RC-2 Workspace persistence evidence not materialized
- Symptom set:
  - no `~/.yai/run/data/<ws>` artifacts during run.
- Class: `db/store/read-path + data-plane persistence + graph materialization`.
- Severity: `S1`.
- Primary owner: `yai`.

### RC-3 CLI readiness messaging drift
- Symptom set:
  - lifecycle output vs doctor/inspect truth divergence.
- Class: `runtime output contract drift`.
- Severity: `S2`.
- Primary owner: `yai-cli`.

### RC-4 SDK scripted stability fragility
- Symptom set:
  - one scripted `sdk make test` failure, standalone rerun green.
- Class: `sdk drift (execution harness stability)`.
- Severity: `S3`.
- Primary owner: `yai-sdk`.

## 4) Repo ownership map

- `yai`: RC-1, RC-2, part of RC-3, composition-to-direct promotion debt.
- `yai-cli`: RC-3, family preflight diagnostics, operator error contract clarity.
- `yai-sdk`: RC-4 and deterministic smoke runner hardening.
- `yai-law`: no blocking drift found in this run; maintain registry/cli parity checks.
- Cross-repo: keep manual pack and matrix synchronized with real runtime behavior.

## 5) Operator impact assessment

Blocking impact:
- rich workspace usage is not practically executable in current run conditions.

Non-blocking impact:
- taxonomy/help/discoverability are in good shape,
- law and sdk structural alignment checks are mostly green.

## 6) WSV-8 recommended closure scope (audit output)

WSV-8 must target:
1. runtime readiness/control-plane availability convergence (`S1`)
2. workspace creation/binding/persistence post-conditions (`S1`)
3. lifecycle/status/readiness output contract coherence (`S2`)
4. representative family e2e proof (graph/db/data/policy) on live runtime (`S2`)
5. sdk smoke determinism in combined wave execution (`S3`)

Out-of-scope deferral candidate:
- full direct-ID replacement for all composition-backed subcommands (acceptable phased `S3` follow-up if operator path is otherwise green).
