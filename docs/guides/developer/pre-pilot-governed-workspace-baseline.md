# Pre-Pilot Governed Workspace Baseline

## Purpose

This document is the canonical pre-pilot closeout baseline for governed workspace flows.
It consolidates what is already operational and repeatable across governance attachment, workspace flow readability, runtime resolution, and inspect/debug/evidence visibility.

Anchor scenario:

- `docs/guides/developer/governed-flow-vertical-slice.md`

Execution assets:

- runbook: `docs/runbooks/operations/developer-runbooks/pre-pilot-governed-flow-runbook.md`
- expected outputs guide: `docs/runbooks/operations/developer-runbooks/pre-pilot-expected-outputs.md`
- readiness checklist: `docs/guides/developer/checklists/pre-pilot-readiness-checklist.md`

## Scope covered now

- discoverable governable objects (embedded LAW index)
- explicit workspace governance attachment
- deterministic workspace context declaration
- runtime law resolution and policy effect output
- event-surface readability (`declared/business/enforcement` split)
- workspace operational state readability (`last_event`, stack, effect, review_state, trace)
- repeatable vertical slice script and matrix integration

## Executive technical summary: what is ready now

Ready now:

- governance objects are explicit and attachable to workspace (`policy_attach` / `policy_detach` runtime surfaces)
- workspace can expose both event semantics and operational flow state
- business specialization is preserved even when enforcement gate is generic
- effective stack / authority / evidence / trace are inspectable in a single run path
- digital governed vertical slice is repeatable through automated integration script
- pre-pilot demo matrix includes hostile, scientific, digital and vertical-slice tracks

## Explicit limits and non-goals

Not provided by this baseline:

- full workflow/review engine with queue lifecycle
- policy authoring UI
- database-backed dataplane
- graph-backed lineage reasoning
- full multi-tenant production governance administration
- industrialized pilot rollout packaging

## Cross-repo capability mapping

- `law`: normative source (packs, overlays, manifests, governable object catalog)
- `yai`: sovereign runtime (workspace binding/state, law resolution, event/operational surfaces, enforcement)
- `sdk`: mediation layer and consumer-side contract shaping (`cli -> sdk -> yai`)
- `cli`: operator-facing command and rendering surface

Current implementation status in this closeout pass:

- runtime and baseline docs/scripts are consolidated in `yai`
- `law/sdk/cli` mapping is documented; no new feature expansion performed in this pass

## Readiness claims supported

Claims that are currently supportable:

- "Governance is no longer implicit: objects are attachable and inspectable."
- "Workspace is no longer only a technical container: it exposes governed operational state."
- "Runtime decisions are explainable with effect/authority/evidence/trace and business/enforcement split."
- "A digital governed vertical slice is repeatable via script."

Claims intentionally excluded:

- "pilot-ready enterprise workflow platform"
- "complete policy lifecycle automation"
- "production-grade multi-tenant governance fabric"

## Immediate next step after pre-pilot baseline

1. Consolidate one customer-specific use-case package on top of the same slice path.
2. Add minimal local DB dataplane for persistent governed run history.
3. Harden review lifecycle from `review_state` summary to concrete state machine.
4. Finalize CLI/SDK UX convergence for operational-state rendering and attach/effective ergonomics.

## Residual gaps tracked

- attachability constraints are still partially descriptive versus fully enforced policy matrix
- conflict engine (`conflicts_with`) is baseline-level, not advanced semantic arbitration
- full end-to-end customer self-service policy management remains a post-baseline step
