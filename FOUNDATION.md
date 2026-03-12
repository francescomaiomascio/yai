# Foundation

YAI is a governed OS-substrate system where authority is explicit, execution is deterministic,
and externally relevant effects are traceable.

This repository is the single canonical system root.

## Layer model

- **L0 Foundation/Contracts**: `foundation/`, `specs/`, `formal/`
- **L1 Kernel Privileged Core**: `kernel/` (ABI, state/lifecycle, admission, containment, grants roots)
- **L2 System Services**: `sys/` (orchestration, daemon, policy, governance, graph, data, network, observability)
- **L3 User Surfaces**: `user/` (CLI, shells, libs, tools, examples)

## Non-negotiable principles

- **Single source of truth**: code, specs, tests, tooling, and docs converge in one repo
- **No silent side effects**: effectful transitions require explicit command/policy path
- **Auditability**: decisions and evidence are reconstructible from persistent records
- **Bounded authority**: each layer has explicit ownership and non-bypassable boundaries
- **Spec-first implementation**: contracts are normative and implementation follows

## Canonical topology

- `boot/`
- `kernel/`
- `sys/`
- `user/`
- `runtime/` (`compatibility/`, `shims/`, `migration/` transitional only)
- `protocol/`
- `data/`
- `specs/`
- `formal/`
- `foundation/`
- `tests/`
- `tools/`
- `docs/` (`transitional/` currently authoritative for historical docs)

## License

Apache-2.0.
