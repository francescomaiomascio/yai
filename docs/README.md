---
role: support
status: active
audience: all
owner_domain: docs
depends_on: [docs/architecture/overview/system-overview.md,docs/architecture/README.md]
---
# YAI Documentation

# Purpose
Provide the official entrypoint for current platform documentation.

## Scope
Covers navigation for architecture, reference, guides, runbooks, program, policies, generated, and archive.

## What Belongs Here
- Canonical entrypoints for live documentation families.
- Surface governance boundaries for live/generated/archive separation.

## What Does Not Belong Here
- Migration or closeout narrative details.
- Section-local procedures and low-level reference content.

## Navigation Order
1. `architecture/overview/system-overview.md`
2. `architecture/overview/subsystem-map.md`
3. `architecture/overview/repository-map.md`
4. `architecture/`
5. `reference/`
6. `guides/`
7. `runbooks/`
8. `program/`
9. `policies/`
10. `generated/`
11. `archive/`

## Extension Rules
- New root entrypoints require canonical-surface policy compliance.
- Live docs must map to real repository surfaces (`foundation/`, `formal/`, `include/yai/`, `lib/`, `cmd/`, `tests/`).
- Historical material is archive-only.

## Canonical Documentation Surface
### Live canonical families
- `docs/architecture/`
- `docs/reference/`
- `docs/guides/`
- `docs/runbooks/`
- `docs/program/`
- `docs/policies/`

### Non-live families
- `docs/generated/` for machine-generated output.
- `docs/archive/` for historical and non-authoritative material.

### Admission minimum
1. Live docs must declare role, status, and owner domain.
2. New live docs must not duplicate canonical owner docs.
3. Historical delivery/refactor material is archive-only.

# Relationships
- `foundation/`
- `formal/`
- `include/yai/`
- `lib/`
- `cmd/`
- `tests/`

# Canonical Role
Root documentation entry contract.

# Main Body
Use this page to enter the canonical live documentation surface.

# Related Docs
- `docs/architecture/README.md`
- `docs/policies/live-docs-admission-policy.md`
