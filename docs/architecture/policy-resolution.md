# Policy Resolution

## Resolution order

`yai` resolves normative decisions from embedded law with this order:

1. foundation baseline
2. domain policy pack
3. applicable compliance layers
4. overlays (currently minimal hook)

## Resolver responsibilities

The resolver:

- loads manifests and resolution-order files
- composes effective normative stack
- applies precedence rules
- handles conflicts and fallback
- computes final runtime effect

## Runtime effects

Resolved effects are runtime-facing and finite:

- `allow`
- `deny`
- `quarantine`
- `review_required`
- `degrade`
- `require_justification`

## Determinism

Resolution is deterministic for the same input context and embedded law version.

Outputs include both effect and rationale so enforcement receives policy plus traceability.
