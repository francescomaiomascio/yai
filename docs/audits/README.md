---
id: AUDITS-README
status: active
owner: governance
effective_date: 2026-02-19
---

# Audits

This directory contains audit-grade assessments and supporting material.

## Structure

- `AUDIT-TRL-0001-yai-program-readiness.md`
  Program-level readiness assessment (narrative + TRL rubric).
- `AUDIT-TRL-0001-evidence-index.md`
  Evidence inventory and execution index for TRL-0001.
- `scorecards/`
  Per-repository scorecards (`yai-specs`, `yai`, `yai-cli`, `yai-mind`).
- `evidence/TRL-0001/`
  Artifact pointers and captured outputs for TRL-0001.
- `findings/`
  Optional granular finding records (one file per finding).

## Conventions

- Use stable IDs (`AUDIT-*`, `SC-*`, `FINDING-*`).
- Keep commands and results reproducible (date + command + outcome + pointer).
- Prefer repo-relative links.
