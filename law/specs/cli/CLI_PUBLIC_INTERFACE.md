# YAI CLI Public Interface (v1)

This document defines the canonical public interface for the `yai` control suite.
It is normative. Implementations must conform.

## Scope

- Applies to the `yai` binary (Rust) and any future front-end (TUI/GUI/agents).
- The CLI is the primary interface. TUI/GUI are front-ends that invoke the same command semantics.

## Principles

1. Single Source of Truth: command semantics are defined here and in `commands.v1.json`.
2. Deterministic execution: commands must be reproducible and observable.
3. Layer boundaries remain (L1 kernel authority, L2 engine deterministic execution, L3 mind orchestration).
4. Every command supports machine output via `--json` where applicable.
5. Side effects are explicit (process spawn/kill, SHM touch, socket IO, filesystem writes).
6. Control plane is authoritative: CLI is a client and must not bypass RPC.

## Global Conventions

### Naming
- Binary: `yai`
- Subcommands: `yai <group> <action>` or `yai <action>` for top-level lifecycle.
- Flags: `--kebab-case`

### Output modes
- Default: human-readable text
- Optional: `--json` for structured output

### Exit codes
- `0` success
- `1` generic failure
- `2` invalid arguments / contract violation
- `3` dependency missing (binary not found, config missing)
- `4` runtime not ready (handshake/vault/socket not ready)

### Default Workspace
- A workspace id (`--ws`) identifies a runtime instance.
- If omitted, `ws_default` is loaded from config.

### Control Plane Paths (Canonical)
These paths are authoritative and mirror `law/specs/control/CONTROL_PLANE.md`:

- `~/.yai/run/<ws>/control.sock`
- `~/.yai/run/<ws>/lock`
- `~/.yai/run/<ws>/daemon.pid`
- `~/.yai/run/<ws>/session.json`
- `/tmp/yai_runtime.<ws>.sock`

## Command Groups

### Lifecycle
- `yai up`
- `yai down`
- `yai restart`

### Runtime Inspection
- `yai status`
- `yai ps`
- `yai logs`

### Control
- `yai providers`
- `yai sessions`

### Vault / Protocol
- `yai vault inspect`
- `yai vault dump` (optional, gated)

### Verification (Gates)
- `yai verify core`
- `yai verify law-kernel`
- `yai verify full`

### TUI / Monitor
- `yai tui run` (canonical full-screen cockpit)
- `yai tui snapshot --view <overview|graph|events|logs|db|providers|contracts|chat>` (canonical JSON snapshot)
- `yai monitor` (legacy alias, deprecated; maps to `yai tui run`)
- `yai events` (stream events)

## Command Contracts (summary)

### `yai up`
Purpose: start the runtime stack (boot + engine + mind) under a workspace id.

Required invariants:
- I-001 traceability
- I-002 determinism
- I-006 external effect boundary

Usage:
- `yai up --ws <id> [--build] [--ai] [--no-engine] [--no-mind] [--detach] [--monitor] [--timeout-ms <n>]`
- `--monitor` is deprecated and maps to `yai tui run`.

Side effects:
- may spawn processes
- may create pidfiles/logfiles
- may create socket(s)

### `yai tui`
Purpose: live cockpit and deterministic snapshots. Must not mutate state unless explicitly asked.

Usage:
- `yai tui --ws <id> run`
- `yai tui --ws <id> snapshot --view overview|graph|events|logs|db|providers|contracts|chat`

Notes:
- `yai monitor --ws <id>` is a deprecated alias for `yai tui --ws <id> run`.
- TUI is a rendering of the same interface. It does not invent actions.
- Navigation and keymap contract is defined in `law/specs/cli/TUI_COCKPIT_V1.md`.

### `yai providers`
Purpose: discovery, trust, and attach/detach of LLM providers.

Usage:
- `yai providers discover --ws <id>`
- `yai providers list --ws <id>`
- `yai providers pair <id> <endpoint> <model> --ws <id>`
- `yai providers attach <id> [--model <m>] --ws <id>`
- `yai providers detach --ws <id>`
- `yai providers status --ws <id>`

### `yai sessions`
Purpose: list/kill active sessions.

Usage:
- `yai sessions list`
- `yai sessions kill <ws> [--force]`

(…continued in `commands.v1.json` for full detail)
