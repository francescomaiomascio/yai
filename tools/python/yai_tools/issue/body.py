from __future__ import annotations

from yai_tools.issue.templates import (
    canonical_milestone_title,
    render_mp_closure_body,
    render_phase_issue_body,
)


def generate_issue_body(title: str, issue_type: str, mp_id: str, runbook: str, phase: str) -> str:
    issue_type_norm = issue_type.strip().lower()
    if issue_type_norm == "phase":
        return render_phase_issue_body(
            track="N/A",
            phase=phase,
            rb_id=title.strip() or "RB-N/A",
            rb_anchor=runbook,
            mp_id=mp_id,
        )
    if issue_type_norm in {"mp-closure", "mp_closure"}:
        return render_mp_closure_body(
            track="N/A",
            phase=phase,
            mp_id=mp_id,
            milestone_title=canonical_milestone_title("N/A", phase),
        )

    return f"""## Type
{issue_type}

## Title
{title}

## IDs
- MP-ID: {mp_id}
- Runbook: {runbook}
- Phase: {phase}

## Objective
- One clear objective.

## Acceptance Criteria
- [ ] Positive evidence included
- [ ] Negative evidence included

## Commands / Repro
```bash
# exact commands
```
"""
