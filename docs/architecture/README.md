# Architecture

This directory contains human-readable system architecture.
It explains intent, component responsibilities, and model-level boundaries.

Architecture documents are explanatory.
They never override normative contract/spec definitions.

## Contents

- `docs/architecture/overview.md`: high-level architecture narrative
- `docs/architecture/runtime-model.md`: runtime layout and responsibilities
- `docs/architecture/specs-bridge.md`: normative boundary and citation rules
- `docs/architecture/components/`: component-level focused pages

## How to read

Recommended order:
1. `overview.md`
2. `runtime-model.md`
3. `specs-bridge.md`
4. relevant component docs

## Normative boundary

If a statement in `docs/architecture/` conflicts with `deps/yai-specs/`,
`deps/yai-specs/` is the source of truth.
