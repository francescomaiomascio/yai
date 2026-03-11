# C17 Docs Audit

Date: 2026-03-11

## Summary

`docs/` had overlapping domains and mixed audience/function boundaries.
Primary collisions found:

- `developer/` vs `developers/`
- `architecture/` vs `platform/architecture/`
- `interfaces/` vs `reference/`
- runbooks split across `developer/`, `program/23-runbooks/`, and misc areas
- `_generated/` not first-class

## Canonical decisions

- Unified audience guides under `docs/guides/`.
- Unified runbook execution content under `docs/runbooks/`.
- Unified technical reference under `docs/reference/`.
- Canonical architecture under `docs/architecture/`.
- Program governance under normalized `docs/program/{rfc,adr,milestone-packs,templates,policies,reports}`.
- Historical/migration material under `docs/archive/`.
