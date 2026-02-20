# GitHub Templates (YAI)

This repo enforces a consistent workflow: issues are structured, PRs are auditable, and changes are reviewable.

## What you get
- Issue forms (bug/feature/runbook/docs)
- Multiple PR templates (default + governance + milestone + twin PR)
- CI gate that rejects PRs without the required PR body structure

## The rule (canonical)
1) Prefer: **Issue -> Branch -> Commits -> Push -> PR -> Review/Merge**
2) Every PR must use a template and must include:
   - Issue-ID (or N/A with Issue-Reason only when allowed)
   - Base-Commit (40-char SHA)
   - Evidence + commands run

## Program Governance Linkage
PR templates are the **tactical layer** for metadata quality.
Program execution governance (Project v2, milestone model, closure discipline) is defined in:
- `docs/dev-guide/github-program-governance.md`
- `docs/dev-guide/github-milestone-template.md`
- `docs/dev-guide/github-issue-templates.md`

Operational rule:
- Use PR templates to guarantee required fields.
- Use PMO governance model to decide when a phase can be closed.

## When an Issue is mandatory
Default: **always** create an issue first.

Allowed exception (rare):
- Repo-tooling / governance bootstrap changes
- Tiny doc fixes that do not affect behavior

If you use the exception, you MUST put:
- `Issue-ID: N/A`
- `Issue-Reason: <why this PR is allowed without an issue>`

## UI vs GH CLI
Either is fine. What matters is that the PR body matches the template fields.

Recommended:
- If you use `gh`: paste or supply the template body.
- If you use UI: select the right template from the dropdown and fill it.

## Branch naming (recommended)
- `feat/<area>-<short>` for behavior changes
- `docs/<topic>-<short>` for docs/governance
- `fix/<area>-<short>` for bugs

## Notes
- Agents (Codex) may create branches and push commits.
- Opening PRs and merging should be done by the maintainer (you).

## Tool-assisted workflow
You can generate a correct PR body locally:

```bash
tools/bin/yai-pr-body --template default --issue 123 --out /tmp/pr.md
```

Then paste /tmp/pr.md into the PR description (UI or GH CLI).

## Tool-assisted workflow (dev commands)
Use canonical helpers to avoid drift:

```bash
tools/bin/yai-dev-milestone-body --track contract-baseline-lock --phase 0.1.0 --rb-anchor docs/runbooks/contract-baseline-lock.md#0.1.0 --mp-id MP-CONTRACT-BASELINE-LOCK-0.1.0 --out .pr/MILESTONE_BODY.md
tools/bin/yai-dev-issue phase --track contract-baseline-lock --phase 0.1.0 --rb-id RB-CONTRACT-BASELINE-LOCK --title "Pin Baseline Freeze" --rb-anchor docs/runbooks/contract-baseline-lock.md#0.1.0 --mp-id MP-CONTRACT-BASELINE-LOCK-0.1.0 --repo yai-labs/yai
tools/bin/yai-dev-branch --type feat --issue 123 --area governance --desc phase-canonization
tools/bin/yai-dev-pr-body --template default --issue 123 --mp-id MP-CONTRACT-BASELINE-LOCK-0.1.0 --runbook docs/runbooks/contract-baseline-lock.md#0.1.0 --classification DOCS --compatibility A --out .pr/PR_BODY.md
tools/bin/yai-dev-pr-check .pr/PR_BODY.md
```
