# GitHub Milestone Template (PHASE)

Canonical milestone title:
- `PHASE: <track>@<phase>`

Use this body template when creating or updating a milestone.

```markdown
## Objective
<single phase objective>

## Runbook Anchor
- `docs/runbooks/<track>.md#<phase>`

## Done When
- [ ] Phase issue is open and actively maintained
- [ ] All required implementation PRs are merged
- [ ] Gate status is `Passed`
- [ ] MP Closure issue is completed and closed
- [ ] Evidence links are reviewable and reproducible

## Required MP
- `MP-<TRACK>-<phase>`

## Evidence Requirements
- [ ] Link all phase PRs
- [ ] Link gate logs (CI and local verify where relevant)
- [ ] Link proof-pack / verification artifacts when applicable
- [ ] Explicit close decision captured in MP Closure issue
```

CLI helper:

```bash
tools/bin/yai-dev-milestone-body \
  --track contract-baseline-lock \
  --phase 0.1.0 \
  --rb-anchor docs/runbooks/contract-baseline-lock.md#0.1.0 \
  --mp-id MP-CONTRACT-BASELINE-LOCK-0.1.0
```
