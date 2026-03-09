# Workspace Governance Targeting And Apply Model

This model describes how governance objects become operational in a workspace
through explicit checks and visible state transitions.

## Runtime stages

1. `target_selection`: choose object + workspace.
2. `eligibility_check`: workspace/family/specialization target match.
3. `dry_run_compatibility`: preview blockers, warnings, precedence impact.
4. `attach`: object enters workspace attachment set.
5. `activate`: attached object becomes active in effective composition.
6. `effective_stack_contribution`: policy effective/debug reflect contribution.
7. `detach`: remove object from active attachment set.

## State semantics

- `eligible` / `ineligible` represent target match.
- `dry_run_passed` / `conflict_blocking` represent compatibility outcome.
- `attached_active` and `inactive` activation labels are exposed by runtime.

## Command IDs

- `yai.workspace.policy_dry_run`
- `yai.workspace.policy_attach`
- `yai.workspace.policy_activate`
- `yai.workspace.policy_detach`
- `yai.workspace.policy_effective`

## Visibility contract

Workspace surfaces expose:

- attachment IDs and count
- eligibility/compatibility/conflict summary
- attachment and activation state
- effective stack reference
- authority/evidence impact through policy effective and debug resolution
