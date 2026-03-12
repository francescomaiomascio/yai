# Container Domain (Canonical)

`container/` is the canonical contained operational domain in YAI.

## Architectural role

- Container owns operational domain identity, lifecycle, root, state, services, and scoped views.
- Kernel owns privileged roots: containment primitives, session admission root, grants validity root, system lifecycle root.
- Orchestration coordinates work on/among containers but does not own container truth.
- Daemons attach/bind to containers; they do not replace container domain ownership.

## Legacy status

`workspace` is legacy migration vocabulary only.
Operational work, scoped session binding, and runtime views are container-centric.
