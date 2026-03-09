---

> Historical topology note: this runbook may use root/kernel/engine labels from earlier waves.
> Canonical runtime ingress now is `yai` on `~/.yai/run/control.sock`.
id: RB-DATA-PLANE
title: Data Plane Program
status: draft
owner: runtime
effective_date: 2026-03-09
revision: 3
supersedes:
  - RB-DATA-PLANE@rev2
  - RB-DATA-PLANE@rev1
depends_on:
  - RB-ROOT-HARDENING
  - RB-WORKSPACES-LIFECYCLE
  - RB-ENGINE-ATTACH
adr_refs:
  - docs/program/22-adr/ADR-006-unified-rpc.md
  - docs/program/22-adr/ADR-007-workspace-isolation.md
  - docs/program/22-adr/ADR-009-engine-attachment.md
  - docs/program/22-adr/ADR-011-contract-baseline-lock.md
  - docs/program/22-adr/ADR-012-audit-convergence-gates.md
decisions:
  - docs/program/22-adr/ADR-006-unified-rpc.md
  - docs/program/22-adr/ADR-007-workspace-isolation.md
  - docs/program/22-adr/ADR-011-contract-baseline-lock.md
  - docs/program/22-adr/ADR-012-audit-convergence-gates.md
related:
  adr:
    - docs/program/22-adr/ADR-006-unified-rpc.md
    - docs/program/22-adr/ADR-007-workspace-isolation.md
    - docs/program/22-adr/ADR-009-engine-attachment.md
    - docs/program/22-adr/ADR-011-contract-baseline-lock.md
    - docs/program/22-adr/ADR-012-audit-convergence-gates.md
  specs:
    - ../law/REGISTRY.md
    - ../law/contracts/control/schema/control_call.v1.json
    - ../law/contracts/control/schema/exec_reply.v1.json
    - ../law/contracts/control/schema/authority.v1.json
    - ../law/contracts/protocol/include/transport.h
    - ../law/contracts/protocol/include/yai_protocol_ids.h
    - ../law/contracts/vault/include/yai_vault_abi.h
    - ../law/contracts/vault/schema/vault_abi.json
    - ../law/registry/commands.v1.json
  test_plans:
    - ops/evidence/qualification/test-plans/hardfail.md
  tools:
    - tools/bin/yai-check-pins
    - tools/bin/yai-verify
    - tools/bin/yai-gate
    - tools/bin/yai-suite
tags:
  - runtime
  - data-plane
  - storage
  - audit-convergence
---

# RB-DATA-PLANE - Data Plane Program (rev3)

## 1) Purpose
Refound the canonical Data Plane model for the current system state.

This tranche is not about "adding databases". It defines the model that all
backend work must follow:
- storage classes,
- ownership boundaries,
- authoritative write/read paths,
- non-bypass rules,
- role model for backend families.

Canonical delivery path remains:
`cli -> sdk -> yai` (with `law` as normative source and `ops` as evidence sink).

## 2) DP-1 Positioning

### What DP-1 is
- Canonical model refoundation.
- Program framing reset from legacy topology language to current runtime reality.
- Storage-class and ownership normalization across `core`, `exec`, `brain`.

### What DP-1 is not
- No heavy backend cutover yet.
- No "winner takes all" backend choice.
- No query-first/cockpit-first implementation.

## 3) Legacy Framing Declassed
Legacy root/kernel/engine labels are retained for historical traceability, but
they are no longer the dominant conceptual frame for Data Plane design.

`mind-redis-stm.md` is explicitly declassed from "DP center" to a backend- and
component-specific runbook:
- Redis is a candidate backend for a storage class, not the Data Plane model.
- Brain is one major DP owner/consumer, not the whole DP.

## 4) Canonical Storage Classes

DP-1 formalizes these classes as canonical system vocabulary:

1. Workspace Operational State
2. Authority State
3. Governance/Compliance Object State
4. Review/Approval/Apply State
5. Event Log
6. Resolution/Evidence Log
7. Artifact Metadata
8. Brain Graph Memory
9. Transient Cognition / STM

These classes are the basis for DP-2..DP-9 and must not be merged prematurely.

## 5) Ownership Model (by Runtime Layer)

### `core` owns
- workspace operational state,
- authority state,
- runtime attachment/apply state anchoring.

Anchors:
- `lib/core/workspace/*`
- `lib/core/authority/*`
- `lib/core/session/*`

### `exec` owns
- execution-time event production,
- storage mediation gates,
- sink-facing runtime writes under governance.

Anchors:
- `lib/exec/runtime/*`
- `lib/exec/gates/storage_gate.c`

### `law-facing governance lifecycle` owns
- governance/compliance object state semantics,
- review/approval/apply lifecycle constraints,
- evidence/audit mapping semantics.

Anchors:
- `lib/law/mapping/decision_to_evidence.c`
- `lib/law/mapping/decision_to_audit.c`

### `brain` owns
- graph memory persistence semantics,
- transient cognition state semantics.

Anchors:
- `lib/brain/memory/*`
- `lib/brain/memory/graph/*`

### `DP substrate` owns
- persistence invariants,
- sink contracts,
- topology discipline,
- backend role enforcement.

## 6) Non-Bypass Rules (authoritative)

1. CLI/SDK never write storage backends directly.
2. Workspace/authority/apply state cannot be mutated outside canonical runtime paths.
3. Governance lifecycle state cannot be bypassed by sink writes.
4. Event/evidence logs are sink contracts, not debug-file side channels.
5. Transient cognition is not authoritative persistent truth.
6. Graph hot cache cannot replace graph truth persistence.
7. Any backend integration must preserve deterministic reply semantics.

## 7) Backend Role Model (not backend dogma)

### KV / embedded authority backend role
Candidate role: workspace operational + authority + apply/lifecycle essentials.
Candidate technologies: LMDB-class stores.

### Tabular / query-oriented backend role
Candidate role: event/evidence/resolution logs and operator-readable summaries.
Candidate technologies: DuckDB-class stores.

### Graph persistence backend role
Candidate role: semantic/episodic persistent graph state.

### Transient memory backend role
Candidate role: STM/hot activation cache/degraded-tolerant cognition sets.
Candidate technologies: Redis-class stores.

No backend is "the Data Plane". Backend choice follows class ownership and sink
contracts, not the reverse.

## 8) Sink-First Strategy (program rule)

Execution order is mandatory:
1. storage classes,
2. topology/layout,
3. sink contracts,
4. write paths,
5. persistence implementation,
6. reader/query surfaces,
7. richer workspace↔graph↔workflow semantics.

This block is intentionally sink-first, not query-first.

## 9) Scope Control (what this block does not do yet)

Out of scope for initial DP block:
- distributed federation/replication/HA,
- cross-workspace rich federated queries,
- distributed graph fabric,
- full workflow persistence,
- advanced policy analytics fabric,
- full cockpit data fabric.

## 10) Program Mapping (DP block in 9 deliveries)

### DP-1 — Refoundation of the Canonical Data Plane Model
Canonical model, terminology, boundaries, ownership, non-bypass baseline.

### DP-2 — Canonical Storage Classes and Backend Role Model
Class-by-class role matrix, backend role binding, non-overlap contracts.

### DP-3 — Canonical Storage Topology and Persistence Layout
Persistence topology, layout contract, migration-safe path model.

### DP-4 — Event and Evidence Sink Hardening
Append/read contracts, retention hooks, deterministic failure semantics.

### DP-5 — Governance and Compliance Persistence Integration
Persistent model for governance/compliance/lifecycle state with law alignment.

### DP-6 — Authority and Artifact Metadata Store Integration
Authority and artifact metadata persistence under runtime ownership boundaries.

### DP-7 — Brain Graph Sink and Transient Cognition Backend
Graph truth vs transient cognition separation, sink contract integration.

### DP-8 — CLI/SDK Data Surfaces and Operator Query Model
Operator/programmatic data surfaces over canonical sinks (no backend bypass).

### DP-9 — Verification, Qualification and Pre-Pilot Data Closure
Cross-repo verification, qualification evidence, pre-pilot closure package.

## 11) Immediate DP-1 Exit Criteria

DP-1 is complete when:
1. canonical storage classes are explicit and stable,
2. ownership model is explicit per class,
3. non-bypass rules are explicit and testable,
4. backend role model is explicit without hard lock-in,
5. sink-first sequence is explicit and accepted,
6. DP-1..DP-9 program map is stable and published.

## 12) Verification Matrix (DP baseline)

Mandatory lanes:
- model/doc consistency checks,
- pin/contract checks against `law`,
- workspace scope and path-jail checks,
- deterministic error semantics checks,
- cross-link integrity for program/runbook references.

Evidence minimum:
- command outputs,
- logs,
- verification reports,
- traceability pointers to runbook phase and claim IDs.

## 13) Failure Modes and Controls
- Cross-tenant leakage:
  - control: workspace boundary + path-jail enforcement.
- Contract drift:
  - control: pin checks + contract anchor verification.
- Backend-role drift:
  - control: class-role matrix checks and review gates.
- File-first regression:
  - control: sink contract enforcement and lifecycle gating.
- Contract drift risk:
  - Control: pin checks + registry/schema anchor validation.
- Runtime/backend mismatch risk:
  - Control: deterministic error mapping and startup validation.
- Non-reproducible closure risk:
  - Control: evidence publication in `ops` with stable pointers.

## 12) Rollback policy
- Roll back the active DP phase branch only.
- Restore last verified baseline for workspace layout and stores.
- Re-run mandatory checks before reopening phase.
- Do not forward-port partial schema/runtime changes without pin realignment.

## 13) Traceability and closure mapping
- Audit convergence:
  - `docs/program/audit-convergence/EXECUTION-PLAN-v0.1.0.md`
  - `docs/program/audit-convergence/AUDIT-CONVERGENCE-MATRIX-v0.1.0.md`
- Related runbooks:
  - `docs/program/23-runbooks/root-hardening.md`
  - `docs/program/23-runbooks/workspaces-lifecycle.md`
  - `docs/program/23-runbooks/engine-attach.md`
- Evidence destination:
  - `ops/evidence/qualification/`
  - `ops/evidence/validation/`

## 14) Definition of Done (rev3)
- All DP-1..DP-9 deliveries closed with explicit evidence links.
- No unresolved drift between code behavior and pinned law contracts.
- Workspace data-plane operations are deterministic and isolated.
- CLI/SDK data commands are governance-routed, not storage-coupled.
- Audit convergence matrix updated from partial to closed for Data Plane scope.
