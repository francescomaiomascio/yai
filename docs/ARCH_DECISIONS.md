# Architecture Decisions (Law-Aligned)

This document captures *architectural* commitments made during system design.
It is intentionally stable and grounded in `law/` invariants.

---

## ADR-001 — Multi-Tenant Runtime (Target)

**Decision**
Adopt a **single runtime per machine** (kernel + engine), with **multiple workspaces**.

**Constraints**
- Every runtime-bound request MUST carry `ws_id`.
- Kernel/engine MUST enforce per-workspace isolation (no cross-ws effects).
- Storage/logs/trace MUST remain per-workspace.

**Law Alignment**
L1/L2 enforce authority and effect boundaries; L3 remains proposal-only.

**Status**
Target architecture (design locked; implementation staged).

---

## ADR-002 — Mind Per Workspace

**Decision**
Maintain **one Mind per workspace** (control plane, graph, provider state).

**Rationale**
Mind is proposal-only (L3) and must remain isolated; cross-ws inference would
violate traceability and external-effect boundaries.

**Status**
Current architecture and long-term commitment.

---

## ADR-003 — Protocol Contract (Strict)

**Decision**
RPC must enforce:
- `protocol_handshake` (version+capability check)
- `arming + role=operator` for privileged commands
- `ws_id` required on all runtime-bound requests (target with multi-tenant runtime)

**Status**
Handshake + arming/role enforced now; `ws_id` becomes mandatory with multi-tenant runtime.

---

## ADR-004 — Event Schema Versioning

**Decision**
All events MUST include:
- `schema_id`
- `event_version` (or `v`)

Non-conforming events are rejected or flagged.

**Status**
`schema_id` enforced; validation policy may tighten over time.

---

## Implementation Phases (Summary)

1. **Protocol & Gate (now)**: enforce handshake, arming/role; introduce `ws_id` in envelope.
2. **Runtime Routing**: kernel/engine accept `ws_id` and route to per-ws state.
3. **Isolation & Audit**: deny cross-ws effects; per-ws logs/vault/graph.
4. **Migration**: dual mode (legacy per-ws runtime vs. multi-tenant) until cutover.

