# YAI TUI Cockpit v1

This document defines the canonical behavior of `yai tui`.
It is normative for the interactive cockpit and its snapshot mode.

## Canonical Commands

- `yai tui --ws <id> run`
- `yai tui --ws <id> snapshot --view overview|graph|events|logs|db|providers|contracts|chat`

Legacy alias:

- `yai monitor --ws <id>` (deprecated, maps to `yai tui --ws <id> run`)

## Runtime Contract

- TUI is a client of control plane and graph/db/log interfaces.
- TUI must not bypass RPC contracts for lifecycle control.
- TUI must not write runtime state directly.
- Snapshot mode must be deterministic for the selected view at call time.

## Views

- `overview`
- `graph`
- `events`
- `logs`
- `db`
- `providers`
- `contracts`
- `chat`

## Navigation Legend

- `Tab`: next view
- `Shift+Tab`: previous view
- `o`: Overview
- `g`: Graph
- `e`: Events
- `l`: Logs
- `d`: DB
- `p`: Providers
- `c`: Contracts
- `h`: Chat
- `:`: toggle command palette
- `Backspace`: edit palette input
- `Enter`: run palette command
- `q`: quit

## Chat Composer Contract

- When focus is on `Composer`, text input must not trigger global view shortcuts.
- `Enter`: send message
- `Shift+Enter`: newline
- `Ctrl+U`: clear composer
- `Esc`: move focus back to navigator
- `C`: commit draft
- `x`: discard draft
- `s`: toggle streaming
- `t`: cycle commit target (`none|events|memory|graph|code`)

## Notes

- `yai tui run` renders in the current terminal session (full-screen alternate screen).
- External terminal spawn behavior, when present, is an implementation detail of legacy `monitor` path and is not required by this spec.
