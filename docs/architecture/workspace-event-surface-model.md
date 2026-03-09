# Workspace Event Surface Model

## Purpose

This model defines the canonical `governable event surface` for workspace execution.
It clarifies where YAI intercepts flow semantics and how those semantics are preserved from declared scenario to final enforcement.

## Canonical Event Surface

A workspace event is the runtime-governed unit emitted by `yai.workspace.run` (or equivalent runtime control call) and materialized in workspace inspect/policy/debug surfaces.

A governable event must expose at least:

- `event_id`
- `workspace_id`
- `declared_scenario_specialization`
- `business_specialization`
- `enforcement_specialization`
- `flow_stage`
- `external_effect_boundary`
- `resolution_trace_ref`
- decision summaries (`effect`, `authority`, `evidence`)

## Flow Stage Taxonomy

YAI uses a compact stage taxonomy for event readability:

- `ingress`
- `retrieve`
- `transform`
- `approve`
- `publish`
- `distribute`
- `egress`
- `actuate`
- `unknown`

The taxonomy is business-readable and intentionally orthogonal to low-level technical gates.

## Three-Layer Specialization Semantics

### 1. Declared scenario specialization

User/workspace intentional context (for example: `remote-publication`, `remote-retrieval`, `artifact-distribution`).

### 2. Business specialization

Resolved semantic business meaning preserved for operator interpretation and workflow narration.

### 3. Enforcement specialization

Technical specialization actually used by enforcement path (for example: `network-egress`).

## Anti-Collapse Rule

When enforcement collapses to a generic technical gate (`network-egress`) but the declared scenario is more specific, the event surface preserves business specialization from declared context.

This guarantees that inspect/debug/effective views can show both:

- business scenario meaning
- enforcement gate meaning

## Declared vs Inferred vs Derived

- Declared fields come from workspace/user context.
- Inferred fields come from classifier/discovery/resolution.
- Derived event-surface fields are computed summaries used for inspectability and policy explainability.

## Surface Integration

The event surface is exposed in:

- `yai.workspace.inspect`
- `yai.workspace.policy.effective`
- `yai.workspace.debug.resolution`
- `yai.workspace.run` reply payload

It is also materialized into workspace-owned containment state (`state_surface` and manifest effective-state fields).

## Scope and Limits

This model strengthens runtime readability and boundary explainability.
It does not yet provide:

- full workflow orchestration
- graph-level lifecycle modeling
- OS-level sandbox enforcement semantics
