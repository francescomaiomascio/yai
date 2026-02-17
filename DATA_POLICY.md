# Data Policy

## Scope

This policy governs dataset assets committed in this repository under `data/`.

## Canonical Dataset Location

- `data/datasets/`
- Current example dataset: `data/datasets/global-stress/v1/`

## Data Content Rules

Datasets in this repository:

- must be non-sensitive test/evaluation data
- must not include personal data (PII), credentials, secrets, or tokens
- must include provenance context sufficient for review

## Contribution Requirements

When adding or updating datasets:

- provide source/provenance and intended use
- ensure content is reproducible and reviewable
- avoid opaque binaries unless clearly justified

## Runtime Artifacts

Runtime-generated logs/events/state are not datasets and must not be committed.
Use runtime directories for generated artifacts and keep them out of git.

## License

Dataset policy text is licensed under Apache-2.0.
