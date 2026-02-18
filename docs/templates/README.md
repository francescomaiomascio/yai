# Documentation Templates (Canonical)

This directory is the only canonical source for documentation templates.

## Available templates

- Runbook: `docs/templates/runbooks/RB-000-template.md`
- ADR: `docs/templates/adr/ADR-000-template.md`
- Proposal: `docs/templates/proposals/PRP-000-template.md`
- Milestone Pack: `docs/templates/milestone-packs/MP-000-template.md`

## Why centralized templates

Centralization avoids drift and keeps structure consistent for humans and agents.
It also simplifies validation and review expectations.

## Rule

Subfolder `README.md` files in `docs/` must reference templates from this directory.
Do not duplicate template files in topic folders.
