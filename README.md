# ICE Foundation — Axiomatic System Design

[![Status](https://img.shields.io/badge/status-foundational%20research-6B7280?style=flat)](#)
[![Scope](https://img.shields.io/badge/scope-axioms%20%26%20invariants-111827?style=flat)](#)
[![Docs](https://img.shields.io/badge/docs-ICE%20Documentation-8FB9FF?style=flat)](https://francescomaiomascio.github.io/ice-docs/)

---

## What this repository is

This repository defines the **axiomatic foundations** of the ICE ecosystem.

ICE Foundation does not describe *how* systems are implemented.
It defines **what must be true** for an ICE-compliant system to exist at all.

The content here establishes:
- non-negotiable invariants
- execution assumptions
- architectural constraints that all other ICE components must obey

These foundations are **systemic**, not stylistic.

---

## Scope

ICE Foundation is concerned with:

- execution as a first-class concept  
- authority and control as explicit system properties  
- state as a derived, inspectable artifact  
- separation between inference and governance  
- observability as a structural requirement  

It operates **above implementation**, but **below architecture**.

---

## What this repository is not

ICE Foundation is **not**:

- a framework
- a runtime
- an engine
- a set of APIs
- a reference implementation

No code lives here by design.

This repository exists to prevent architectural drift as systems evolve.

---

## Core assumptions

ICE systems assume that:

- intelligence does not imply authority  
- inference does not imply action  
- state must be explainable after the fact  
- long-running systems must survive failure  
- execution must remain intelligible over time  

These assumptions are treated as **axioms**, not preferences.

---

## Relationship to the ICE ecosystem

ICE Foundation constrains all other ICE components.

- `ice-runtime` must enforce these invariants  
- `ice-engine` must operate within them  
- orchestration layers must not bypass them  
- agents and models are subordinate to them  

Dependencies flow **one way only**:
from foundation to implementation.

---

## Documentation

This repository is complemented by:

📘 ICE Documentation & RFCs  
https://francescomaiomascio.github.io/ice-docs/  
https://github.com/francescomaiomascio/ice-docs

---

## Support

ICE Foundation is part of an independent, long-term research effort.

If you are interested in:
- execution-level system design  
- governance of intelligent systems  
- runtime-centric AI architectures  

you can support the work here:

- GitHub Sponsors  
  https://github.com/sponsors/francescomaiomascio
