# Workspace State Surface Model

## Identity surface
Stored in `manifest.json`.

## Mutable operational state
Stored in `state/workspace-state.json` with:
- declared context
- inferred context
- effective refs
- governance attachments
- event surface refs
- operational state summary
- inspect refs

## Runtime-local state
Stored in `runtime/runtime-state.json` with routing and attachment fields.

## Validity markers
`namespace_valid` and `boundary_reason` are derived and exposed through status/inspect/debug surfaces.


Operational readability contract: `docs/architecture/workspace-flow-state-model.md`.
