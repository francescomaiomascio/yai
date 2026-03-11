# Workspace Flow/State Model

## Purpose

The workspace is both:

- a containment and binding boundary
- an operational flow cell for governed execution

This model defines the minimum readable operational state that a workspace must expose.

## State dimensions

A workspace flow/state is composed of:

- identity state
- binding/session state
- declared context state
- inferred context state
- governance attachment state
- last governed event state
- effective stack state
- operational outcome state
- review/escalation state
- trace/evidence visibility state

## Canonical operational state fields

Minimum operational fields:

- `workspace_id`
- `binding_state`
- `declared_context`
- `inferred_context`
- `attached_governance_objects`
- `active_effective_stack`
- `last_event_ref`
- `last_flow_stage`
- `last_business_specialization`
- `last_enforcement_specialization`
- `last_effect`
- `last_authority`
- `last_evidence`
- `last_trace_ref`
- `review_state`
- `operational_summary`

## Persistence vs derivation

Persisted workspace state:

- identity/lifecycle
- declared and inferred context checkpoints
- effective summaries
- attachment set
- trace refs and inspect refs

Derived state (from last resolution and event surface):

- flow stage
- business vs enforcement specialization split
- review state
- operational summary

Session-transient state:

- process-bound handles
- transient control-call payload internals

## Operational readability contract

`inspect`, `policy effective`, and `debug resolution` must expose:

- attachment visibility
- last governed event visibility
- effective stack + precedence visibility
- outcome and review-state visibility
- trace/evidence visibility

This keeps the workspace readable as a flow cell, not only as a technical container.

## Boundary with workflow engine

This model intentionally stops before full workflow orchestration:

- no queue engine
- no multi-step approval lifecycle engine
- no external dataplane persistence

It is a deterministic local state model designed to support vertical slices and later workflow layers.
