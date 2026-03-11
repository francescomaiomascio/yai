# Governance

## Scope

This document governs the `yai` unified repository convergence model.

- Canonical governance destination: `governance/`
- Canonical naming namespace: `governance` (`law` is transitional compatibility naming)
- Runtime implementation: `cmd/`, `include/`, `lib/`
- Canonical documentation center: `docs/`
- Migration-only area: `transitional/`

If implementation and contracts diverge, implementation must be corrected.

## Spec-First Process

For contract-facing changes:
1. Define/update normative governance content in canonical governance roots.
2. Align runtime implementation in `yai`.
3. Verify with CI, qualification waves, and runtime checks.
4. Keep migration markers only under `transitional/`.

## Documentation Residency

`docs/` is first-class and central in this repository.

Cross-repo references may exist during migration, but canonical architecture/program guidance must remain readable from this root.

## Required Review Areas

- Governance/model updates and compatibility impact
- Kernel authority/enforcement boundaries
- Engine external effect gating
- Runtime protocol behavior
- Edge/mesh/workspace behavior under sovereignty boundaries
- Migration safety (`embedded/` and legacy paths must not be re-canonized)

## License

Apache-2.0.
