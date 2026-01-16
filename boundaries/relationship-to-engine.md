# Boundary: Foundation → Engine / Infrastructure

## Purpose

Define the boundary between the **ICE Foundation**
and the **ICE Engine / Infrastructure** domain.

This document establishes what the Foundation constrains
with respect to system construction and operation,
and what it explicitly does **not** define or control.

The goal is to prevent architectural authority
from leaking into implementation or operational concerns.

---

## Role of the Foundation

The ICE Foundation:

- Defines axioms that constrain system meaning
- Defines structural invariants that Engine must preserve
- Establishes conceptual validity
- Sets non-negotiable constraints on what systems are allowed to mean

The Foundation does **not** describe systems.

---

## Role of Engine / Infrastructure

Engine / Infrastructure:

- Defines how systems are built, deployed, and operated
- Implements mechanisms that preserve invariants
- Manages resources, topology, and execution substrates
- Adapts systems to physical and operational constraints

Engine answers **how systems exist**,
never **what is true**.

---

## Explicit Non-Responsibilities of the Foundation

The Foundation does NOT define:

- Infrastructure topology
- Deployment models
- Hardware or cloud assumptions
- Resource management strategies
- Scaling or availability mechanisms
- Fault tolerance or redundancy models
- Operational constraints

All such concerns belong exclusively to Engine design.

---

## Constraint Relationship

- The Foundation constrains **meaning**
- The Engine realizes **structure**
- The Engine may change implementation
- The Foundation may not be reinterpreted

If an Engine design violates an invariant,
the Engine is incorrect — not the Foundation.

---

## Invalid Boundary Violations

The following are invalid:

- Encoding infrastructure assumptions as axioms
- Justifying implementation choices via Foundation text
- Allowing operational constraints to redefine invariants
- Treating Foundation as an architecture specification

Such actions violate the boundary.

---

## Canonical Status

This boundary is authoritative.

Any Engine or Infrastructure layer claiming ICE compliance
must demonstrate alignment with this boundary.

The Foundation constrains Engine meaning.  
Engine never extends Foundation authority.
