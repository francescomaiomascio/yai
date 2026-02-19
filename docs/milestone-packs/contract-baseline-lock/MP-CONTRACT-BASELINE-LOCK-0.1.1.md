---
id: MP-CONTRACT-BASELINE-LOCK-0.1.1
status: draft
runbook: docs/runbooks/contract-baseline-lock.md
phase: "0.1.1 — CI Parity on Contract Surfaces"
adrs:
  - docs/design/adr/ADR-011-contract-baseline-lock.md
spec_anchors:
  - deps/yai-specs/contracts/invariants/I-001-traceability.md
  - deps/yai-specs/contracts/invariants/I-002-determinism.md
  - deps/yai-specs/contracts/invariants/I-003-governance.md
issues:
  - N/A
issue_reason: "Foundational docs track creation; issue ID not assigned yet."
---
# MP-CONTRACT-BASELINE-LOCK-0.1.1

## Metadata

- Runbook: `docs/runbooks/contract-baseline-lock.md`
- Phase: `0.1.1 — CI Parity on Contract Surfaces`
- Owner: `governance`
- Status: `draft`

## Links

- ADR: `docs/design/adr/ADR-011-contract-baseline-lock.md`
- Proposal: `docs/design/proposals/PRP-002-unified-rpc-and-cli-contract.md`
- Evidence plans: `docs/test-plans/hardfail.md`

Objective:
- Enforce parity checks on protocol and authority contract surfaces across consumers.

Contract Delta:
- Envelope: none.
- Authority: none.
- Errors: parity failures must be hard-fail in CI.
- Logging: CI artifacts must show parity outcomes for both repos.

Repo Split:
- `yai`: parity checks over contract-facing code paths and pins.
- `yai-cli`: parity checks over contract-facing commands and vectors.

Evidence Plan (minimum):
- Positive cases:
  - Both repos pass parity checks against the same baseline.
  - Re-run is deterministic with unchanged inputs.
- Negative cases:
  - Contract drift in one repo causes CI failure.
  - Pin mismatch causes parity check failure.

Compatibility Classification:
- Type: A
- Rationale: validation hardening only; no wire contract redesign.
- Upgrade path: existing conformant behavior remains supported.

Definition of Done:
- [ ] CI parity checks are active and non-optional in both repos.
- [ ] Drift between repos is detected and blocks merge.
- [ ] Evidence artifacts are attached for review.
- [ ] Traceability links to ADR-011 and runbook phase are present.
