# YAI Architecture Decisions (Law-Aligned, 2026 Revision)

This document captures the **machine-level architecture commitments**
of YAI as of the current runtime refactor phase.

It is grounded in `deps/yai-specs/contracts/` invariants and reflects the
post-envelope, post-authority enforcement state.

The architecture is stratified across:

- L0 — Vault (immutable identity & ABI boundary)
- L1 — Kernel (authority, sessions, isolation)
- L2 — Engine (execution gates)
- L3 — Mind (proposal-only cognition per workspace)
- Root — Machine Control Plane (runtime governor)

---

## ADR-001 — Single Runtime Per Machine (Canonical)

### Decision

YAI runs as **one machine-level runtime**, composed of:

- Root Control Plane
- Kernel (L1)
- Engine (L2)

This runtime manages multiple workspaces concurrently.

### Implications

- No per-workspace daemon model long-term.
- No direct CLI-to-workspace socket access.
- The runtime is machine-scoped, not workspace-scoped.

### Constraints

- All runtime-bound requests MUST carry `ws_id`.
- Kernel MUST enforce isolation between workspaces.
- Engine MUST execute effects only under Kernel authority.
- Cross-workspace state sharing is forbidden by default.

### Law Alignment

- A-002 Authority
- I-006 External Effect Boundary
- L1/L2 boundary enforcement

### Status

Architecture locked.
Implementation staged (Root stub active, full multi-tenant pending).

---

## ADR-002 — Root Control Plane as Canonical Entry Point

### Decision

Introduce a **Root Control Plane** as the only public entrypoint
for CLI and cockpit.

All external clients MUST connect to:

    ~/.yai/run/root.sock

Workspace sockets are internal-only.

### Responsibilities (Root)

- Runtime health & status
- Workspace registry
- Workspace spawn/attach/detach
- Machine-level boundary enforcement
- Routing to workspace plane

### Non-Goals

- Root does NOT execute engine gates
- Root does NOT host Mind logic
- Root does NOT mutate workspace memory

Root is a governor, not an executor.

### Rationale

Prevents:

- Direct CLI → workspace bypass
- Unauthorized multi-tenant conflicts
- Daemon explosion per workspace

### Status

Stub implementation active.
Routing layer under integration.

---

## ADR-003 — Kernel as Authority Plane (L1)

### Decision

Kernel is the **authority enforcement layer**.

It validates:

- protocol version
- handshake
- role
- arming flag
- ws_id
- session ownership

It is the only layer that may authorize effectful execution.

### Enforcement Rules

- `arming=true` requires role ≥ operator
- No execution without handshake
- No execution before workspace attach
- No cross-workspace session mixing

### Non-Goals

- Kernel does not perform business logic
- Kernel does not execute provider/storage logic
- Kernel does not own cognition

### Status

Authority enforcement active.
Session locking stabilized (robust PID validation).

---

## ADR-004 — Engine as Execution Plane (L2)

### Decision

Engine is the **execution gate layer**.

It provides:

- storage_gate
- provider_gate
- network_gate
- resource_gate
- cortex execution

Engine executes only after Kernel authorization.

### Rules

- Engine never validates authority
- Engine never selects workspace
- Engine never bypasses Kernel

### Relationship

Kernel → Engine (downward call)
Engine → Kernel (never)

### Status

Engine routing stub integrated.
Full integration with Root pending.

---

## ADR-005 — Mind Per Workspace (L3 Cognitive Plane)

### Decision

Each workspace owns one Mind instance.

Mind is:

- workspace-scoped
- proposal-only
- non-authoritative

Mind may:

- build graph state
- generate plans
- propose actions

Mind may NOT:

- execute external effects
- bypass Engine
- access other workspaces

### Rationale

Preserves:

- Cognitive isolation
- Determinism
- Law invariants

### Status

Mind remains per-workspace Rust process.
Future consolidation possible under runtime governance.

---

## ADR-006 — Strict Unified RPC Contract

### Decision

All communication follows a single binary envelope contract:

Envelope fields:

- magic
- version
- ws_id
- trace_id
- command_id
- role
- arming
- payload_len

### Mandatory Rules

- Handshake required
- `ws_id` required for runtime-bound commands
- `arming + role` required for privileged commands
- Deterministic error responses (with ws_id + trace_id)

### Prohibited

- Parallel protocols
- JSON-only side channels
- CLI-specific shortcuts

### Status

Envelope enforcement active.
CLI authority injection active.

---

## ADR-007 — Workspace Isolation Model

### Decision

Workspace isolation is enforced at three levels:

1. Session lock (PID-based lockfile)
2. Memory isolation (per-ws storage paths)
3. RPC routing (Root-bound dispatch)

### Lockfile Policy

- Lockfile contains PID
- Stale lock detection via kill(pid, 0)
- Stale locks auto-recovered

### Status

Robust lock logic active.
Future: move from file-lock to runtime registry model.

---

## ADR-008 — Connection Lifecycle Semantics

### Decision

Connections are one of:

- root session
- workspace-attached session

Handshake establishes protocol validity.
Attach establishes workspace context.

### Rules

- No execution before attach
- Attach must be explicit
- Reconnect must re-handshake

### Status

One-shot CLI stable.
Persistent cockpit session model pending.

---

## ADR-009 — Engine Attachment Model (Next Phase)

### Decision

Engine will be attached to Root runtime,
not directly spawned per workspace.

Workspace context will be passed through dispatch layer.

### Future Model

Root
 ├── Kernel (authority)
 ├── Engine (shared execution plane)
 └── Workspace contexts (logical isolation)

### Status

Planned.
Not yet fully integrated.

---

## ADR-010 — Boot as Canonical Machine Entry

### Decision

`yai` (boot) is the only official runtime entrypoint.

It performs:

- preboot validation
- directory integrity
- root socket creation
- runtime initialization

Direct launching of workspace kernel binaries is deprecated.

### Status

Migration in progress.
Boot canonicalization required before engine integration.

---

# Implementation Phases (Updated)

A — Envelope + Authority (Completed)
B — Root Control Plane Canonicalization (In Progress)
C — CLI Migration to Root Socket (Required)
D — Workspace Attach Protocol (Next)
E — Engine Shared Integration
F — True Multi-Tenant Runtime Cutover
G — Authority Lease & Anti-Replay
H — Delegated Scoped Capabilities
I — Deterministic Audit Layer

---

# Architectural North Star

One Machine Runtime  
Many Workspaces  
One Authority Plane  
One Execution Plane  
Many Cognitive Planes  

Law enforced at L1.  
Effects executed at L2.  
Proposals generated at L3.  
Governed by Root.
