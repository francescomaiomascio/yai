# Embedded Law Surface

`embedded/law/` is the runtime-facing law export inside `yai`.

## Purpose

Provide a reduced, versioned, validated law surface for runtime consumption without mirroring the full law repository.

## Contains

- `VERSION`
- `COMPATIBILITY.json`
- `law.manifest.json`
- `runtime.entrypoints.json`
- `domains/index/*`
- `domains/D*/...` runtime-facing domain packs
- `compliance/index/*`
- `compliance/*` runtime-facing compliance packs
- `manifests/*` export/runtime manifests
- `generated/*` summaries and runtime-resolution view

## Does not contain

- full law docs/authoring narratives
- complete authority/foundation/formal corpus
- refactor archives
- non-runtime-facing internal law tooling

## Lifecycle

- source of truth: `law`
- generation boundary: `law/manifests/embedded-export.manifest.json`
- sync command: `tools/bin/yai-law-embed-sync`
- local validation command: `tools/bin/yai-law-compat-check`
