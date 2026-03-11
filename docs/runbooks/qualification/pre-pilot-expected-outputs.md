# Expected Outputs and Interpretation Guide

## Purpose

This guide maps key output signals to technical meaning for pre-pilot demonstrations.

## Step: governance attachment

Signal:

- attach command returns `ok`
- attached object appears in `policy_attachments` / `attached_governance_objects`

Interpretation:

- governance is explicit and workspace-scoped, not implicit default-only behavior

## Step: workspace inspect

Signals to check:

- declared context present
- `event_surface` present
- `operational_state` present
- `attached_governance_objects` contains expected object id

Interpretation:

- workspace is acting as a governed flow cell, not only a session container

## Step: event run output

Signals to check:

- `decision.family_id` and specialization fields are coherent
- `event_surface.declared_scenario_specialization` visible
- `event_surface.business_specialization` visible
- `event_surface.enforcement_specialization` visible
- `operational_state.review_state` set (`blocked|quarantined|pending_review|clear`)

Interpretation:

- business semantics are preserved independently from enforcement gate specialization

## Step: policy effective

Signals to check:

- effective stack reference present
- authority/evidence summaries present
- `operational_state.active_effective_stack` not empty

Interpretation:

- composition is real and inspectable, not only final effect rendering

## Step: debug resolution

Signals to check:

- trace reference present
- declared/inferred/effective context and event surface are coherent
- operational summary readable (`flow/business => effect`)

Interpretation:

- explainability path is operational: rationale can be audited with trace linkage

## Outcome classes and meaning

- `deny`: blocked path
- `quarantine`: suspended pending further review/sink checks
- `review_required`: controlled path requiring review checkpoint
- `allow`: clear path under current stack

## Demonstration rule

During demos, always pair an output with:

1. what changed in governance/context
2. what changed in event surface
3. what changed in outcome/evidence

This avoids output-only storytelling and keeps the explanation technically grounded.
