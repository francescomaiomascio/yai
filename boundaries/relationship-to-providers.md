# Boundary: Foundation ↔ Providers

## Purpose

Define and formalize the **conceptual boundary** between the **ICE Foundation**
and **External Providers**.

This document establishes that external platforms, services, vendors,
and dependencies are **non-foundational** and must never influence,
extend, or redefine axioms, structural invariants, or conceptual validity.

The goal is to prevent **vendor authority**, **service behavior**, or
**dependency constraints** from collapsing into foundational truth.

---

## Foundational Position

The ICE Foundation is **internally authoritative** and **provider-agnostic**.

It defines:

- Axioms that establish what is assumed to be true
- Structural invariants that constrain authority, traceability, and determinism
- Conditions under which delegation is conceptually valid
- Limits on what may or may not depend on external systems

The Foundation does **not** depend on providers.

---

## Role of the Foundation

The ICE Foundation:

- Defines invariant constraints on delegation
- Establishes what must remain true regardless of provider behavior
- Constrains how authority may be delegated externally
- Preserves conceptual validity independent of dependencies

The Foundation defines **what must not change**,  
not **who supplies capabilities**.

---

## Role of Providers

ICE Providers:

- Supply external capabilities (compute, storage, models, services)
- Implement integrations with third-party platforms
- Expose vendor-specific APIs and operational constraints
- May change, degrade, or fail independently of ICE

Providers answer **where capabilities come from**,  
never **what is valid** or **what is allowed**.

---

## Explicit Non-Responsibilities of the Foundation

The ICE Foundation does **NOT** define, select, or manage:

- Vendor or platform choice
- Cloud, on-premise, or hybrid strategies
- External model or service providers
- Cost, billing, quotas, or pricing
- Availability, redundancy, or SLA guarantees
- Credential management or secrets handling
- Integration-specific error handling

All such concerns belong **exclusively** to the Providers domain.

---

## Constraint Relationship

The relationship is strictly asymmetric:

- The Foundation constrains **delegation semantics**
- Providers implement delegated capabilities
- Providers may fail, change, or disappear
- The Foundation must remain conceptually unaffected

If a provider violates an invariant,
the integration is invalid — not the Foundation.

---

## Boundary Violations

The following constitute **boundary violations**:

- Encoding provider assumptions as axioms or invariants
- Treating provider behavior as authoritative truth
- Allowing vendor limitations to redefine constraints
- Hard-coding provider semantics into foundational documents
- Inferring validity from service availability

Such actions invalidate ICE compliance.

---

## Canonical Status

This boundary definition is **canonical and authoritative**.

Any provider integration claiming ICE compliance
must demonstrate that external dependencies operate
strictly within the constraints defined here.

The Foundation constrains Providers.  
Providers never redefine the Foundation.