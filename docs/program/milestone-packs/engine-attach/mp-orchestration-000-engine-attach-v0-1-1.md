---
id: MP-ENGINE-ATTACH-0.1.1
status: draft
runbook: docs/program/milestone-packs/runtime-baselines/mp-runtime-000-engine-attach.md
phase: "0.1.1 — EA-1 control-plane semantic hardening"
adrs:
  - docs/program/adr/adr-orchestration-009-engine-attachment.md
  - docs/program/adr/adr-workspace-008-connection-lifecycle.md
  - docs/program/adr/adr-protocol-006-unified-rpc.md
spec_anchors:
  - ../law/contracts/protocol/include/transport.h
  - ../law/contracts/control/schema/exec_reply.v1.json
  - ../law/contracts/control/schema/authority.v1.json
claims:
  - C-KERNEL-HARD-BOUNDARY-CORE
  - C-CONTEXT-PROPAGATION
evidence_commands_required:
  - tools/bin/yai-verify
  - tools/bin/yai-suite
issues:
  - "N/A: engine-attach wave sequencing"
---

# MP-ENGINE-ATTACH-0.1.1

## Metadata
- Runbook: `docs/program/milestone-packs/runtime-baselines/mp-runtime-000-engine-attach.md`
- Phase: `0.1.1 — EA-1 control-plane semantic hardening`
- Status: `draft`

## Objective
Harden deterministic engine start/stop/status behavior at kernel authority boundary.

## Mandatory command outcomes
- `tools/bin/yai-verify` -> `PASS`
- `tools/bin/yai-suite` -> `PASS`

Closure policy: mandatory `SKIP` is treated as `FAIL`.

## Definition of Done
- [ ] Deterministic responses on success/failure.
- [ ] Error mapping aligned to canonical contract payload semantics.
- [ ] No silent drop paths.
- [ ] Evidence links and command outputs archived.

## Execution Snapshot
- Status: `PLANNED`
- Evidence bundle: `docs/program/milestone-packs/engine-attach/evidence/0.1.1/`
