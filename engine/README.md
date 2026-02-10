# yai-engine

L2 Engine implementation. This module is runtime-critical and must remain compliant with YAI Law.

## Authority Sources

- `../law/axioms/*`
- `../law/invariants/*`
- `../law/boundaries/*` (especially L2 Engine boundary; L1 Kernel gating; L0 Vault contract; YAI Law invariants and axioms.)

## Quickstart

- `make clean && make`
- `../.yai/artifacts/yai-core/bin/yai-engine arch_dev_session`

## Non-goals

No authority, no state machine ownership, no protocol ID changes.
