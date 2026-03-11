# A12 - Agents Mechanical Placement

A12 repositions agents as a governed mechanical subsystem of the unified YAI
system.

## Canonical agents topology

- `lib/agents/runtime/`
- `lib/agents/dispatch/`
- `lib/agents/roles/`
- `lib/agents/safety/`
- `lib/agents/grounding/`
- `lib/agents/execution/`
- `lib/agents/internal/`

## Canonical public agents surface

- `include/yai/agents/runtime.h`
- `include/yai/agents/dispatch.h`
- `include/yai/agents/roles.h`
- `include/yai/agents/safety.h`
- `include/yai/agents/grounding.h`
- `include/yai/agents/execution.h`

## A12 cutover actions

- moved agent implementation files from `lib/exec/agents/` into canonical
  `lib/agents/` subdomains (`roles`, `dispatch`, `safety`).
- aligned build topology to compile agent implementation from `lib/agents/*`.
- retained `include/yai/exec/agents.h` as compatibility shim importing the
  canonical `include/yai/agents/*` surface.

## Boundary model

- orchestration governs plan/flow and execution control.
- agents execute mechanical role tasks inside orchestration-driven flows.
- governance constraints and runtime authority bound agent behavior.
