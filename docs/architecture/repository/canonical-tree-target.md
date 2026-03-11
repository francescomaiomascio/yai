# Canonical Tree Target (A2)

This document defines the official repository topology target for the unified
YAI system.

## Root Macro-Topology

Canonical roots:

- `cmd/`
- `governance/`
- `include/`
- `lib/`
- `docs/`
- `tests/`
- `tools/`
- `data/`
- `transitional/`

Non-canonical/transitional root:

- `archive_tmp/` (temporary migration residue only)
- `embedded/` (legacy surface, not final-state topology)

## Five Primary Masses

1. Runtime implementation: `cmd/`, `include/`, `lib/`
2. Governance content: `governance/`
3. Documentation/reference: `docs/`
4. Validation/tooling: `tests/`, `tools/`, `data/`
5. Migration-control: `transitional/`

## Canonical Role Lock

- `governance/` is the canonical destination for former standalone law content.
- `docs/` is the single central documentation space.
- `transitional/` is the only migration-only area.
- no new canonical content must be introduced under `embedded/`.

## A2 Outcome

A2 instantiates the target topology and placeholder spine so subsequent
refactor/migration slices can attach without another topological redesign.
