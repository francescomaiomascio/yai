# Compatibility Matrix

This matrix defines baseline compatibility for the `yai` runtime.

## Runtime and Specs

| yai | deps/yai-specs | Notes |
|---|---|---|
| main (development) | pinned submodule commit in `deps/yai-specs` | authoritative contracts for current tree |

## Platform Support (Current)

| Platform | Status | Notes |
|---|---|---|
| Linux | Supported | primary runtime target |
| macOS | Supported | development and local-first operations |
| Windows | Not officially supported | no compatibility guarantees yet |

## Toolchain Baseline

| Tool | Requirement |
|---|---|
| C compiler | gcc or clang |
| Build | GNU make |
| Python | Python 3 (scripts/verification helpers) |

## Notes

- Runtime behavior is contract-bound to `deps/yai-specs`.
- If implementation and specs diverge, specs are authoritative.

## License

This policy is part of the Apache-2.0 licensed repository. See `LICENSE` and `NOTICE`.
