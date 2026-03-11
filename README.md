# yai

`yai` is being refounded as the unified system repository target.

## Program intent

The target model is a single repository that hosts:

- runtime implementation (`cmd/`, `include/`, `lib/`)
- governance content (canonical destination: `governance/`)
- documentation and references (`docs/`)
- validation and tooling (`tests/`, `tools/`)
- controlled migration area (`transitional/`)

Program overview:

- `docs/program/repo-unico-overview-32-consegne.md`

## Root rules (A1)

- `governance/` is the canonical governance root for the final unified model.
- `transitional/` is migration-only and must not become a permanent feature root.
- `embedded/` is transitional legacy and must be decommissioned through planned cutover.
- canonical naming is `governance`; `law` naming is legacy compatibility-only.

## Current convergence model

- Block A (A1-A19): refound `yai` root/tree/domains for final unified topology.
- Block B (B1-B13): absorb `law` content into `governance/`, then sunset dual-repo layout.

## Start here

- `docs/README.md`
- `docs/program/repo-unico-overview-32-consegne.md`
- `governance/README.md`
- `transitional/README.md`
