# A11 - Orchestration Refoundation

A11 establishes orchestration as a first-class system domain rather than an
incidental side effect of exec/agent dispatch.

## Canonical orchestration topology

- `lib/orchestration/planner/`
- `lib/orchestration/workflow/`
- `lib/orchestration/actions/`
- `lib/orchestration/supervision/`
- `lib/orchestration/scheduling/`
- `lib/orchestration/execution/`
- `lib/orchestration/coordination/`
- `lib/orchestration/internal/`

## Canonical public orchestration surface

- `include/yai/orchestration/planner.h`
- `include/yai/orchestration/workflow.h`
- `include/yai/orchestration/actions.h`
- `include/yai/orchestration/supervision.h`
- `include/yai/orchestration/scheduling.h`
- `include/yai/orchestration/execution.h`
- `include/yai/orchestration/coordination.h`

## A11 cutover actions

- moved orchestration implementation files from `lib/exec/orchestration/` to
  canonical `lib/orchestration/*` subdomains.
- updated build topology to compile orchestration from canonical paths.
- retained `include/yai/exec/orchestration.h` as compatibility shim to
  canonical orchestration headers.

## Boundary model

- orchestration governs planning, flow transitions, and controlled execution.
- agents provide mechanical execution roles under orchestration control.
- runtime remains owner-side authority core.
- mesh remains distributed topology and peer-state domain.
