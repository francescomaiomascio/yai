# A5 - Law to Governance Naming Cutover

This document records the A5 naming cutover rule for the unified YAI repository.

## Canonical naming rule

`governance` is the canonical namespace for:

- repository paths
- public headers
- implementation domains
- architecture and program language
- runtime integration semantics

## Transitional compatibility rule

`law` naming remains compatibility-only during convergence.

Allowed transitional uses:

- compatibility include shims under `include/yai/law/`
- legacy build/test aliases (`test-law`, `law-embed-*`)
- historical references in archived reports/evidence
- bridge paths under `embedded/law` and `transitional/embedded-law`

Disallowed for new canonical content:

- new primary architecture rooted in `law/*`
- new public API rooted in `yai/law/*`
- new implementation domains rooted in `lib/law/*`

## Cutover status at A5

- canonical public header surface: `include/yai/governance/*`
- compatibility headers: `include/yai/law/*` (shim to governance)
- canonical implementation surface: `lib/governance/*`
- compatibility implementation marker: `lib/law/` (no canonical logic)
- canonical governance content destination: `governance/`
