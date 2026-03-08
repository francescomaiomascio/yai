# User Guide Pointers

This folder contains navigation pointers.
Normative source is canonical `law`, consumed in runtime through `embedded/law`.

## Canonical pointers

- Canonical law manifests and layers: `law/manifests/*`
- Runtime-facing contract in repo: `embedded/law/*`
- Runtime compatibility checks: `tools/bin/yai-law-compat-check`

## Boundary rule

If behavior changes contract/spec semantics, update canonical `law` first and regenerate embedded artifacts.
