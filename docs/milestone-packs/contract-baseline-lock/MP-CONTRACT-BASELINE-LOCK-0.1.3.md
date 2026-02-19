---
id: MP-CONTRACT-BASELINE-LOCK-0.1.3
status: draft
runbook: docs/runbooks/contract-baseline-lock.md
phase: "0.1.3 — Formal/Core Sync on Contract Delta"
adrs:
  - docs/design/adr/ADR-011-contract-baseline-lock.md
spec_anchors:
  - deps/yai-specs/contracts/invariants/I-002-determinism.md
  - deps/yai-specs/contracts/invariants/I-003-governance.md
  - deps/yai-specs/contracts/invariants/I-006-external-effect-boundary.md
issues:
  - N/A
issue_reason: "Foundational docs track creation; issue ID not assigned yet."
---
# MP-CONTRACT-BASELINE-LOCK-0.1.3

## Metadata

- Runbook: `docs/runbooks/contract-baseline-lock.md`
- Phase: `0.1.3 — Formal/Core Sync on Contract Delta`
- Owner: `governance`
- Status: `draft`

## Links

- ADR: `docs/design/adr/ADR-011-contract-baseline-lock.md`
- Proposal: `docs/design/proposals/PRP-005-formal-coverage-roadmap.md`
- Evidence plans: `docs/test-plans/hardfail.md`

Objective:
- Require formal/core verification updates whenever authority or envelope contracts change.

Contract Delta:
- Envelope: contract delta requires corresponding verification delta.
- Authority: contract delta requires corresponding verification delta.
- Errors: merges without required verification updates must fail.
- Logging: traceability evidence must link contract change to verification change.

Repo Split:
- `yai`: core verification artifacts updated for contract deltas.
- `yai-cli`: contract/vector verification updated when CLI surface is impacted.

Evidence Plan (minimum):
- Positive cases:
  - Contract delta with matching verify updates passes all gates.
  - Traceability graph links contract and verify changes.
- Negative cases:
  - Contract delta without verify updates is blocked.
  - Partial verify update without matching contract scope is blocked.

Compatibility Classification:
- Type: B
- Rationale: introduces stricter merge constraints bound to verification obligations.
- Upgrade path: contributors must include synchronized verify deltas when changing contracts.

Definition of Done:
- [ ] Contract deltas trigger required formal/core sync checks.
- [ ] Unsynced deltas are blocked deterministically.
- [ ] Evidence shows explicit contract-to-verify mapping.
- [ ] All links are traceable in docs and CI output.
