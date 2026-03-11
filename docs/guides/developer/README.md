# Developer docs

- Dev guide: `docs/guides/developer/dev-guide/`
- Getting started: `docs/guides/user/getting-started/`
- User guide: `docs/guides/user/user-guide/`

Cross-repo governance:
- `docs/guides/developer/cross-repo-dependency-policy.md`
- `docs/guides/developer/cross-repo-responsibility-matrix.md`
- `docs/guides/developer/cross-repo-pinning-matrix.md`

Workspace runtime model:
- `docs/guides/developer/workspace-inspect-model.md`
- `docs/guides/developer/workspace-prompt-context.md`
- `docs/guides/developer/workspace-policy-inspection.md`
- `docs/guides/developer/workspace-governance-apply-walkthrough.md`
- `docs/guides/developer/event-evidence-sink-walkthrough.md`
- `docs/guides/developer/governance-persistence-walkthrough.md`
- `docs/guides/developer/authority-artifact-persistence-walkthrough.md`
- `docs/guides/developer/brain-graph-and-transient-cognition-walkthrough.md` (legacy filename; canonical content is graph + transient knowledge split)
- `docs/guides/developer/operator-query-walkthrough.md`
- `docs/guides/developer/enforcement-record-closure-walkthrough.md`
- `docs/guides/developer/runtime-record-to-graph-walkthrough.md`
- `docs/guides/developer/filesystem-decommission-walkthrough.md`
- `docs/guides/developer/filesystem-cleanup-execution-walkthrough.md`
- `docs/guides/developer/workspace-first-real-scenario.md`

Pre-pilot closeout pack:
- `docs/guides/developer/pre-pilot-governed-workspace-baseline.md`
- `docs/guides/developer/governed-flow-vertical-slice.md`
- `docs/runbooks/operations/developer-runbooks/pre-pilot-governed-flow-runbook.md`
- `docs/runbooks/operations/developer-runbooks/pre-pilot-expected-outputs.md`
- `docs/guides/developer/checklists/pre-pilot-readiness-checklist.md`
- `docs/guides/developer/checklists/data-plane-pre-pilot-readiness-checklist.md`

## Operational terminology guardrails

Developer walkthroughs in this path are canonical only if they use unified
runtime semantics:

- capability families: `core`, `exec`, `data`, `graph`, `knowledge`
- workspace-first binding for operational context
- readiness semantics that distinguish:
  - runtime liveness,
  - active workspace selection,
  - bound/degraded/unbound capability state.

Legacy subsystem wording (`brain`, `mind`) may appear only as historical aliases
inside explicitly marked historical material.
