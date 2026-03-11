# A4 - Lib Domain Refoundation

This document records the A4 implementation-topology baseline for `lib/`.

## Canonical implementation domains

The canonical `lib/` domains for the unified repository are:

- `runtime/`
- `edge/`
- `mesh/`
- `orchestration/`
- `agents/`
- `providers/`
- `knowledge/`
- `graph/`
- `governance/`
- `data/`
- `protocol/`
- `platform/`
- `support/`
- `third_party/`

## A4 cutover actions

- Governance runtime implementation moved from `lib/law/*` to `lib/governance/*`.
- Build topology aligned by replacing `LAW_SRCS` with `GOVERNANCE_SRCS`.
- `lib/law/` retained as compatibility-only transitional surface.
- Governance implementation sources switched to `yai/governance/*` includes.

## Transitional compatibility

`lib/core/`, `lib/daemon/`, and `lib/exec/` remain present during convergence.
They are compatibility surfaces and must not become the canonical destination
for new implementation domains.
