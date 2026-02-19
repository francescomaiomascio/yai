# Tests

Current executable locations (kept stable):

- `tests/integration`
- `tests/e2e`
- `tests/fixtures`

Preparation layout (non-breaking mini-refactor):

- `tests/domains/boot`
- `tests/domains/kernel`
- `tests/domains/root`
- `tests/domains/engine`
- `tests/shared`

Rules:

- Do not move existing tests unless CI references are updated.
- New tests should be added in `tests/domains/<component>` when possible.
- Keep cross-component scenarios in `tests/integration`.
