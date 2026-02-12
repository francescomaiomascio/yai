# I-007 — Compliance Context Required for External Effects

## Purpose

Define compliance context as a mandatory authority precondition for any
external-effect transition.

## Invariant

For every external-effect transition, YAI must enforce:

`ExternalEffect => compliance_context_valid = TRUE`

and

`ExternalEffect => authority # "NONE"`.

## Runtime Model Binding

The formal kernel model (`law/formal/YAI_KERNEL.tla`) binds this invariant through:

- variable `compliance_context_valid`
- guard `ExternalEffectGuard`
- theorem `[](external_effect => compliance_context_valid)`

## Violation

A transition that sets `external_effect = TRUE` without valid compliance context
is invalid and must be denied.

## Scope

This invariant covers authority checks for external effects.

It does not define:

- DSAR workflow
- retention policy execution
- legal interpretation

Those are downstream compliance workflows built on top of this authority invariant.
