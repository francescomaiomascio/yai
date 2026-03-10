---
id: workspace-verticalization-hardening-backlog-v0.1.0
status: active
owner: runtime-governance
updated: 2026-03-10
related:
  - docs/program/reports/workspace-verticalization-manual-execution-report-v0.1.0.md
  - docs/program/reports/workspace-verticalization-gap-classification-v0.1.0.md
---

# WSV-7 Hardening Backlog (v0.1.0)

Severity:
- `S1` blocks core operator usage
- `S2` major inspectability/usability gap
- `S3` correctness drift with workaround
- `S4` polish/compatibility debt

## Backlog items

### WSV7-HB-001
- Severity: `S1`
- Repo: `yai`, `yai-cli`
- Family: lifecycle / binding (all downstream families impacted)
- Symptom: `lifecycle up` reports reachable/not-ready but subsequent `ws` commands fail `SERVER_UNAVAILABLE`.
- Root-cause hypothesis: runtime bring-up and control endpoint readiness are not converging to an actual reachable control plane in this environment.
- Required fix type: runtime bring-up hardening + readiness gating fix in CLI lifecycle handling.
- Suggested owner: runtime core + CLI runtime surfaces.

### WSV7-HB-002
- Severity: `S1`
- Repo: `yai`
- Family: workspace persistence (`db`, `graph`, `data`)
- Symptom: no workspace artifacts under `~/.yai/run/data/<ws>` after attempted manual flow.
- Root-cause hypothesis: workspace creation/bind never actually reaches runtime; persistence hooks never execute.
- Required fix type: enforce successful workspace create/open/set path with explicit post-conditions and failure diagnostics.
- Suggested owner: runtime workspace lifecycle.

### WSV7-HB-003
- Severity: `S2`
- Repo: `yai-cli`
- Family: lifecycle/status/readiness
- Symptom: inconsistent operator story between `lifecycle up` text and `doctor/inspect runtime`.
- Root-cause hypothesis: lifecycle output currently reports partial liveness without strict correlation to control-plane availability.
- Required fix type: tighten liveness/readiness/bound-state rendering contract and error-path messaging.
- Suggested owner: CLI output/status surfaces.

### WSV7-HB-004
- Severity: `S2`
- Repo: `yai`, `yai-cli`
- Family: graph/db/data/knowledge/policy/recovery/debug
- Symptom: all families blocked at same runtime gate; no per-family degraded context.
- Root-cause hypothesis: preflight gate fails early with generic server-unavailable path.
- Required fix type: preflight diagnostics and actionable hints per family; optional degraded-mode probe.
- Suggested owner: CLI routing + runtime error taxonomy.

### WSV7-HB-005
- Severity: `S3`
- Repo: `yai-sdk`
- Family: SDK smoke execution stability
- Symptom: one scripted wave run failed (`sdk_smoke: context set failed`) while standalone rerun passed.
- Root-cause hypothesis: sequencing/environment race around workspace context file operations or env state handoff.
- Required fix type: stabilize `sdk_smoke` setup/teardown isolation and add deterministic pre-clean in test runner.
- Suggested owner: SDK test harness.

### WSV7-HB-006
- Severity: `S3`
- Repo: `yai-cli`, `yai-sdk`, `yai`
- Family: composition-backed families (`db`, `recovery`, parts of `knowledge`)
- Symptom: canonical commands exist but backend semantics are partly composed over query/inspect/status.
- Root-cause hypothesis: direct runtime IDs not yet fully promoted for all subcommands.
- Required fix type: promote direct runtime handlers incrementally; keep composition paths documented until cutover.
- Suggested owner: runtime mapping + CLI/SDK follow-up wave.

### WSV7-HB-007
- Severity: `S4`
- Repo: `yai`
- Family: manual execution automation
- Symptom: evidence currently in `/tmp` only; not persisted as canonical artifact set.
- Root-cause hypothesis: no dedicated repo script for evidence capture pack.
- Required fix type: add repeatable `tools/` script to run WSV pack and emit structured artifacts under versioned evidence folder.
- Suggested owner: program operations.

## Execution order recommendation

1. `WSV7-HB-001` (runtime readiness gate)
2. `WSV7-HB-002` (workspace persistence post-conditions)
3. `WSV7-HB-003` (status/readiness output coherence)
4. `WSV7-HB-004` (family-level diagnostics)
5. `WSV7-HB-005` (sdk smoke determinism)
6. `WSV7-HB-006` (direct-ID promotion)
7. `WSV7-HB-007` (evidence automation polish)
