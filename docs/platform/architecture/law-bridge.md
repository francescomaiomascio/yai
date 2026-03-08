---
id: ARCH-LAW-BRIDGE
status: active
effective_date: 2026-03-08
revision: 2
owner: governance
law_refs:
  - law/manifests/law.manifest.json
  - law/manifests/publish.layers.json
  - embedded/law/runtime.entrypoints.json
---

# Law Bridge

## Role

Define mandatory citation and alignment rules between `yai` runtime architecture and canonical `law` publish/export contract.

## Rules

- Architecture docs must anchor normative claims to canonical `law` paths or embedded contract artifacts.
- `embedded/law` is the active runtime-facing contract surface.
- `../law` is fallback bridge only and must not be used as primary reference in new docs.
- If implementation diverges from contract intent, record drift with remediation target.

## Citation pattern

Prefer:
- canonical source references (`law/...`)
- runtime contract references (`embedded/law/...`)

Avoid introducing new primary anchors under `../law/...`.
