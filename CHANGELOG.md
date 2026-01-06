# Changelog

All notable changes to **ICE Runtime** are documented in this file.

This project follows a **foundational-first evolution model**:
architectural boundaries and invariants are established early and
refined conservatively over time.

---

## [Unreleased]

### Observations
- Runtime core structure stabilized
- Event kernel formalized with closed taxonomy and append-only storage
- Capability system introduced and enforced at runtime level
- Session and workspace lifecycle defined
- Logging subsystem isolated as non-causal observability layer

This phase focuses on **temporal stability observation**, not feature expansion.

---

## [0.1.0] — Initial Runtime Foundation

### Added
- Runtime authority and execution entrypoint
- Run executor with explicit lifecycle semantics
- Event kernel with:
  - immutable event model
  - centralized emission
  - validation and authority boundaries
  - append-only event store
- Capability registry, grants, and enforcement
- Memory governance:
  - promotion rules
  - lifecycle management
  - agent-scoped views
- Session and workspace management
- Sovereign runtime clock and identifiers
- Structured logging subsystem with pluggable sinks
- Transport abstractions (HTTP, IDE, WebSockets)

### Notes
This release establishes the **architectural spine** of ICE Runtime.
APIs may evolve, but **responsibility boundaries and invariants are considered stable**.

---

## Changelog Policy

- Architectural changes must be reflected here
- Silent semantic drift is not allowed
- Refactors that preserve invariants may omit version bumps
- Any invariant change requires explicit documentation
