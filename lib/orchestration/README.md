# Orchestration Implementation Domain (Canonical)

`lib/orchestration/` is the canonical operational-control domain of the unified
YAI system.

Canonical subdomains:

- `planner/`
- `workflow/`
- `actions/`
- `supervision/`
- `scheduling/`
- `execution/`
- `coordination/`
- `internal/`

Boundary rules:

- orchestration governs plans, flow transitions, execution control, and
  supervision outcomes.
- agents remain mechanical executors under orchestration control.
- mesh coordination and orchestration coordination remain distinct domains.
