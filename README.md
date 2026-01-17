# ICE Foundation — Axiomatic System Design

ICE Foundation defines the **axiomatic layer** of the ICE ecosystem.

Its purpose is not to describe implementations, components, or workflows,
but to establish the **non-negotiable assumptions** under which any ICE-compliant
system is allowed to exist.

Everything built within ICE — runtimes, engines, orchestration layers,
and execution environments — is constrained by what is defined here.

ICE Foundation answers a single class of questions:

> What must always be true for intelligent systems to remain governable,
> inspectable, and coherent over time?

This repository formalizes those answers.

---

## Scope

ICE Foundation addresses execution as a **system property**, not as a byproduct
of inference or intelligence.

It treats authority, control, and state evolution as explicit architectural
concerns, rather than emergent behavior.

Within this scope, the Foundation defines:
- how execution is authorized
- how state is derived and validated
- how side effects are constrained
- how observability is preserved as systems grow in complexity and duration

These concerns are defined independently of programming language, framework,
infrastructure, or deployment model.

The level of abstraction is intentionally positioned:
- below concrete architectural choices
- above implementation details

---

## Nature of the Repository

ICE Foundation is **not** a framework, runtime, engine, or API surface.

It contains no executable code by design.

Its role is to prevent architectural ambiguity and long-term semantic drift by
fixing the conceptual ground on which all other ICE components operate.

All material in this repository is **normative**.
It defines constraints, not suggestions.

---

## Core Assumptions

ICE systems are founded on the following assumptions:

- intelligence does not imply authority
- inference does not imply action
- state must not be opaque or implicit

Any system that acts over time must:
- remain explainable after the fact
- tolerate partial failure
- preserve intelligibility as context accumulates

These assumptions are treated as axioms.
They are not optimized away, negotiated, or conditionally applied.

---

## Position in the ICE Ecosystem

ICE Foundation constrains the entire ICE ecosystem.

- Runtimes enforce these axioms at execution time
- Engines operate within the boundaries they define
- Orchestration layers coordinate behavior without bypassing them
- Agents and models remain subordinate to the authority model established here

Dependencies flow in one direction only:

**from foundation to implementation**

---

## Documentation

This repository is complemented by the canonical ICE documentation and RFCs,
which expand and formalize the concepts introduced here.

https://francescomaiomascio.github.io/ice-docs/
