---
id: RB-SPECS-REFACTOR-FOUNDATION
title: Specs Refactor Foundation
status: draft
owner: governance
effective_date: 2026-02-19
revision: 1
supersedes: []
depends_on:
  - RB-CONTRACT-BASELINE-LOCK (planned)
adr_refs:
  - docs/design/adr/ADR-011-contract-baseline-lock.md
decisions:
  - docs/design/adr/ADR-011-contract-baseline-lock.md
related:
  adr:
    - docs/design/adr/ADR-011-contract-baseline-lock.md
  specs:
    - deps/yai-specs/SPEC_MAP.md
    - deps/yai-specs/REGISTRY.md
    - deps/yai-specs/VERSIONING.md
    - deps/yai-specs/COMPATIBILITY.md
  test_plans: []
  tools:
    - tools/bin/yai-docs-trace-check
    - tools/bin/yai-proof-check
    - tools/release/check_pins.sh
---

# RB-SPECS-REFACTOR-FOUNDATION — Pre-Hardening Specs Program

## 1) Purpose
Create a deterministic pre-hardening foundation for `yai-specs` and consumers before runtime hardening tracks. This runbook extracts the refactor concepts into executable phases with proof gates.

## 2) Preconditions
- [ ] Contract baseline lock sequence is prepared (`ADR-011` baseline available).
- [ ] Cross-repo pin governance is active (`tools/release/check_pins.sh`).
- [ ] No direct development is performed inside consumer `deps/yai-specs` trees.

## 3) Inputs
- Repos: `yai-specs`, `yai`, `yai-cli`
- Canonical references: `SPEC_MAP.md`, `REGISTRY.md`, `VERSIONING.md`, `COMPATIBILITY.md`
- CI/checkers: docs traceability + pin checks + consumer verify scripts

## 4) Sequencing

### Position in the global sequence
1. Contract baseline lock runbook (first)
2. Specs refactor foundation runbook (this document)
3. Root hardening runbook
4. Workspace lifecycle
5. Engine attach
6. Data plane

## 5) Phases

<a id="phase-0-1-0-canonical-tree"></a>
### 0.1.0 — Canonical Tree & Domain Separation
Claim: repository layout is canonical and navigable.
- Scope: docs/contracts/specs/formal/compliance/vectors/tools boundaries.
- Gate: stable tree; no semantic rewrites.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.0.md`

<a id="phase-0-1-1-mapping-only"></a>
### 0.1.1 — Pure Mapping (Move/Rename Only)
Claim: mapping cleanup is structural only.
- Scope: move/rename and dedup placement errors.
- Gate: no content deltas in normative artifacts.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.1.md`

<a id="phase-0-1-2-sanity-links"></a>
### 0.1.2 — Sanity Link & Pointer Health
Claim: no broken links or ghost paths.
- Scope: markdown links, index pointers, SPEC_MAP/REGISTRY references.
- Gate: docs/link check green.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.2.md`

<a id="phase-0-1-3-consumer-yai"></a>
### 0.1.3 — Consumer-Ready Wiring in `yai`
Claim: `yai` consumes specs deterministically under the new structure.
- Scope: pin, include paths, build wiring, verify scripts.
- Gate: `yai` build+verify green.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.3.md`

<a id="phase-0-1-4-consumer-yai-cli"></a>
### 0.1.4 — Consumer-Ready Wiring in `yai-cli`
Claim: `yai-cli` remains aligned and deterministic.
- Scope: pin, include paths, references, vectors/verify.
- Gate: `yai-cli` build/tests/vectors green.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.4.md`

<a id="phase-0-1-5-ci-guardrails"></a>
### 0.1.5 — CI Hard Guardrails
Claim: trivial regressions become non-mergable.
- Scope: docs lint/link, json/schema/vector checks, registry/filesystem consistency, formal smoke.
- Gate: protected branch checks enforce failure on regressions.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.5.md`

<a id="phase-0-1-6-toolchain-policy"></a>
### 0.1.6 — Internal Toolchain & Policy
Claim: validation/format/policy/release operations are repeatable.
- Scope: validate_all/format_all/policy checks/release helpers.
- Gate: local and CI toolchain commands green.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.6.md`

<a id="phase-0-1-7-formal-binding"></a>
### 0.1.7 — Formal Binding & Traceability Matrix
Claim: contracts ↔ specs ↔ vectors ↔ formal mapping is machine-verifiable.
- Scope: coverage map + validator.
- Gate: traceability validator green with explicit coverage outputs.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.7.md`

<a id="phase-0-1-8-tla-reboot"></a>
### 0.1.8 — TLA Reboot & Model-Check CI
Claim: TLA model checks are repeatable and staged (quick/deep).
- Scope: TLA modules/cfg/runners and CI profile split.
- Gate: quick checks always green; deep checks stabilized with mapped invariants.
- Milestone Pack (planned): `docs/milestone-packs/specs-refactor-foundation/MP-SPECS-REFACTOR-FOUNDATION-0.1.8.md`

## 6) Verification
- `tools/bin/yai-docs-trace-check --all`
- `tools/release/check_pins.sh` (mode according to branch/release policy)
- consumer verification commands in `yai` and `yai-cli`

## 7) Failure Modes
- Symptom: consumer pin mismatch after specs move.
  - Fix: realign pins and rerun consumer verify before merge.
- Symptom: docs/index drift after mapping-only phase.
  - Fix: rerun link/sanity checks and restore canonical pointers.
- Symptom: formal mapping not covering invariants.
  - Fix: block phase closure until coverage validator passes.

## 8) Rollback
- Roll back to previous stable specs pin in consumers (`yai`, `yai-cli`).
- Revert mapping commits in the current phase only (no partial mixed-phase merges).
- Re-run pin + docs + verify checks before reopening PR.

## 9) References
- ADR: `docs/design/adr/ADR-011-contract-baseline-lock.md`
- Specs: `deps/yai-specs/SPEC_MAP.md`, `deps/yai-specs/REGISTRY.md`
- MPs (planned): `docs/milestone-packs/specs-refactor-foundation/*`
