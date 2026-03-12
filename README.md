# yai

`yai` is the single canonical repository of the unified YAI system.

## Canonical roots

- boot/kernel substrate: `boot/`, `kernel/`
- system services: `sys/`
- user layer: `user/`
- transitional compatibility: `runtime/compatibility/`
- protocol and data roots: `protocol/`, `data/`
- semantic contracts: `specs/`
- platform formal/foundation: `formal/`, `foundation/`
- docs authority: `docs/`
- verification/tooling: `tests/`, `tools/`

Legacy build surfaces (`cmd/`, `include/`, `lib/`) are no longer root-level owners.
Residual implementation and headers are drained under `runtime/compatibility/`.

## Repository status

- split-repository topology is sunset
- the former separate governance repository is no longer an operational prerequisite for build/test/release in this repository
- embedded and transitional legacy surfaces are removed from active root topology

## Governance model

Governance contracts are authored under `specs/` and consumed by runtime/tooling from canonical
spec and schema paths.

## Start here

- `docs/README.md`
- `specs/README.md`
- `FOUNDATION.md`
- `GOVERNANCE.md`
- `VERSIONING.md`
- `docs/transitional/root-meta/COMPATIBILITY.md`
