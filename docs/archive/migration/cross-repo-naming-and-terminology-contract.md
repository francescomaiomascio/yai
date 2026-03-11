# Cross-Repo Naming and Terminology Contract

Status: active
Owner: ecosystem
Effective date: 2026-03-10

## Purpose

Define one canonical terminology contract across `yai`, `law`, `sdk`, and
`cli` so identical runtime concepts are named identically and interpreted
identically.

This document is normative for active terminology until superseded.

## A. Canonical term set

### Runtime

- Meaning: unified runtime implemented by `yai`.
- Scope: process/runtime control and workspace-scoped capability operation.
- Preferred usage: `runtime`, `unified runtime`.
- Disallowed confusion: detached subsystem runtime narratives.

### Owner runtime

- Meaning: centralized control-plane runtime hosted by `yai`.
- Preferred usage: `owner runtime`, `owner-side runtime`, `yai owner runtime`.
- Disallowed confusion: owner-equivalent runtime on source nodes.

### Source node

- Meaning: remote/local edge node that runs acquisition process.
- Preferred usage: `source node`.
- Disallowed confusion: peer owner runtime.

### YAI daemon

- Meaning: standalone edge acquisition binary.
- Canonical name: `yai-daemon`.
- Scope: distributed acquisition feed into owner runtime truth.
- Disallowed confusion: canonical owner runtime replacement.

### Workspace

- Meaning: canonical runtime binding boundary for scoped capability state.
- Scope: selection, activation, binding, recovery/load, inspect surfaces.
- Preferred usage: `workspace`, `active workspace`, `workspace binding`.
- Disallowed confusion: workspace as path-only metadata.

### Core

- Meaning: lifecycle authority, workspace boundary, foundational control.
- Scope: startup/shutdown authority, workspace sovereignty, baseline runtime
  transitions.

### Exec

- Meaning: execution-facing family.
- Scope: agents, orchestration, execution mediation, gates, execution runtime
  participation.

### Data

- Meaning: persistence and lifecycle family.
- Scope: stores, records, query, retention, archive, binding.

### Graph

- Meaning: relational truth family.
- Scope: graph state, materialization, lineage, summaries, graph query.

### Knowledge

- Meaning: cognition support family.
- Scope: cognition/reasoning support, memory, providers, semantic/episodic/
  activation support.

### Governance

- Meaning: law-driven runtime constraints and decisions.
- Scope: governable objects, primitives, overlays, constraints, policy effects.

### Attachability

- Meaning: allowed governance attachment/apply semantics against runtime
  boundaries.
- Scope: runtime entrypoints, workspace governance attachment, constraints.

### Binding

- Meaning: runtime capability state attached to active workspace context.
- Scope: data/graph/knowledge readiness and runtime operational context.

### Readiness

- Meaning: capability availability under current runtime + workspace context.
- Scope: status surfaces, inspect outputs, operator and SDK contracts.

### Recovery/Load

- Meaning: restoration of runtime/workspace-bound state during activation.
- Scope: workspace open/select recovery path, restored/fresh status.

### Entrypoint

- Meaning: runtime contract ingress surface used by control/command operations.
- Scope: manifests, command taxonomy, SDK/CLI request surfaces.

### Governable object

- Meaning: identity-bearing governance artifact attachable/consumable by runtime
  under lifecycle rules.

### Primitive

- Meaning: canonical law capability unit referenced by governance semantics and
  command/runtime mappings.

### Agent-safe

- Meaning: governance posture constraining what agent-facing actions are allowed
  and under what human/authority boundaries.

### Orchestration

- Meaning: execution coordination behavior in `exec`.
- Disallowed confusion: orchestration as `knowledge` ownership.

## B. Workspace semantics contract

- `workspace` is the primary runtime binding boundary.
- `active workspace` means selected runtime context.
- `workspace binding` means capability context is attached and usable, not only
  selected.
- `workspace attachment` is governance/object attach action within workspace
  model, not detached subsystem attach stage.
- `workspace-first` means capability readiness is evaluated against workspace
  context.
- `recovery/load` belongs to workspace activation path semantics.

## C. Readiness and status contract

- `alive`: process/runtime liveness only.
- `ready`: capability usable in current bound context.
- `bound`: workspace binding applied successfully.
- `attached`: governance/object attach state in workspace lifecycle.
- `available`: capability can be used now.
- `degraded`: capability present with reduced semantics/coverage.
- `unbound`: workspace context not bound.
- `recovered`/`restored`: state loaded from prior persisted runtime/workspace
  context.
- `initialized`: initialization completed for declared phase; not equivalent to
  full readiness.

Liveness and readiness must never be conflated in SDK/CLI/operator surfaces.

## D. Governance and law-facing contract

- Governance targets canonical families and workspace-bound runtime boundaries.
- Runtime entrypoint and attachability semantics must be family-aware and
  workspace-first.
- `law` terms for primitives/governable objects/constraints must stay compatible
  with runtime family ownership.

## E. Forbidden and legacy terminology

### Forbidden in active truth

- `brain` as canonical runtime subsystem.
- `mind` as canonical runtime subsystem.
- `yai-source` as canonical binary name.
- `source runtime` as owner-equivalent topology term.
- `peer runtime` for v1 source-plane topology.
- `federated runtime` for v1 source-plane topology.
- detached cognitive lifecycle or attach-stage wording as current runtime truth.
- umbrella wording that hides `exec`, `data`, `graph`, or `knowledge` ownership.

### Allowed as historical only

- historical references inside explicitly marked legacy/de-authorized material.

### Transitional (explicitly justified only)

- legacy aliases in machine-readable compatibility fields where required for
  migration safety and explicitly marked deprecated/non-canonical.

## F. Allowed abbreviations and ambiguity policy

- `runtime binding` may be shortened to `binding` only in context where runtime
  scope is explicit.
- `knowledge state` may be shortened to `knowledge` in status tables where
  column semantics are defined.
- Preferred canonical form: `workspace binding` (not detached `workspace attach`
  as subsystem-stage phrase).
- Preferred canonical form: `exec runtime` and `execution runtime` are both
  allowed; `exec` is preferred in compact surfaces.

## G. Repo-by-repo impact map

### yai

- Architecture/runtime model docs.
- Runtime startup/status/workspace inspect wording.
- Public headers and family naming.
- Program/runbook terminology for runtime/data/graph/knowledge ownership.

### law

- Runtime-targeting docs and pointers.
- Registry/primitives/governable-object language.
- Runtime entrypoint/attachability manifest and schema wording.
- Historical runtime alias surfaces de-authorized.

### sdk

- Public API names and model wording for workspace/binding/readiness.
- Client docs/examples for status/inspect semantics.
- Avoid alternative topology aliases.

### cli

- Command/help/status wording.
- Workspace inspect and readiness output naming.
- Keep liveness vs readiness distinction explicit.

## H. Cross-repo truth source statement

- Runtime topology truth originates in unified runtime implementation in `yai`.
- `law` runtime targeting aligns to that runtime truth.
- `sdk` and `cli` expose/consume the same model and terminology contract.
- This document is the cross-repo terminology source until formally superseded.

## I. Downstream ownership

- `DX-2`: cross-repo architecture docs cleanup using this contract.
- `DX-3`: runbooks/walkthroughs/developer guides cleanup using this contract.
- `SDK-1..SDK-3`: SDK surface/models/docs/examples alignment.
- `CLI-1..CLI-3`: CLI taxonomy/help/output/docs alignment.
