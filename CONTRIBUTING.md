# Contributing

## Prerequisites

- C toolchain: `gcc` or `clang`
- `make`
- Python 3 for helper scripts used in verification workflows
- Git submodules initialized (`deps/yai-specs`)

## Setup

```bash
git submodule update --init --recursive
make all
```

## Branch and Commit Style

Use focused branches and conventional commit prefixes:

- `feat:` new functionality
- `fix:` bug fixes
- `docs:` documentation/meta changes
- `chore:` maintenance/legal/tooling updates

## Verification Expectations

Before opening a PR, run the checks relevant to your change:

```bash
make all
./tools/bin/yai-verify
./tools/ops/verify-core.sh
./tools/ops/verify-events.sh
```

## Contract-Impacting Changes

For changes that affect protocol/control/graph/vault contracts:

1. Submit contract update in `yai-specs` first (or as tandem PR).
2. Update submodule pointer in this repo after contract approval.
3. Align runtime code and tests to the new pinned contracts.

## Third-Party and Data Rules

- Do not add new external dependencies without documenting license in `THIRD_PARTY_NOTICES.md`.
- If vendoring code, keep upstream license headers/files intact.
- Do not add datasets containing PII or secrets.
- Dataset contributions must include provenance and usage intent.

## Pull Request Checklist

- [ ] No contract/runtime divergence introduced.
- [ ] No new undeclared external dependency.
- [ ] Third-party notices updated when vendoring/importing code.
- [ ] No PII/secrets/runtime logs committed.
- [ ] Relevant verification commands executed successfully.

## License

Contributions are accepted under Apache-2.0.
