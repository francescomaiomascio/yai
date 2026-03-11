# Workspace Block Closeout (WS-6)

WS-6 closes the initial workspace refoundation cycle.

## Closed outcomes

- canonical command path is consistent across `law -> yai -> cli`
- workspace command set is stable (`current/status/inspect/domain/policy/debug/run`)
- first real workspace-driven scenario is implemented (`economic/payments`)
- `workspace.run` resolves using active workspace binding and persists post-action summaries
- negative-path coverage exists for domain validation and binding states
- runbooks/docs now describe one coherent operator flow

## Release-readiness checks

Follow `docs/architecture/workspace-validation-matrix.md`.

## Residual tolerated debt

See `docs/architecture/workspace-transitional-residue.md`.

## Out of scope for WS-6

- dataplane and historical event persistence
- multi-workspace orchestration
- advanced workspace-level user overlays
- full removal of compatibility dotted command aliases
