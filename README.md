# ICE Foundation

[![ICE Ecosystem](https://img.shields.io/badge/ICE-Ecosystem-8FB9FF?style=flat)](#)
[![Docs](https://img.shields.io/badge/docs-ICE%20Docs-8FB9FF?style=flat)](https://github.com/francescomaiomascio/ice-docs)
[![Status](https://img.shields.io/badge/status-foundational-6B7280?style=flat)](#)
[![Governance](https://img.shields.io/badge/type-normative-111827?style=flat)](#)
[![License](https://img.shields.io/badge/license-MIT-7A7CFF?style=flat)](#)

ICE Foundation is the **normative layer** of the ICE ecosystem.

It defines the **laws, invariants, and architectural boundaries** that govern
all ICE components, including engines, runtimes, APIs, applications, and plugins.

ICE Foundation does not execute code.
It establishes **what is allowed, what is forbidden, and what is stable** across
the entire system.

---

## What ICE Foundation Is

ICE Foundation is:

- The **authoritative source of truth** for ICE architecture
- A **versioned and citable body of rules**
- A shared contract between all ICE repositories
- The place where architectural decisions become binding

ICE Foundation is treated as **sovereign**.
Any component that violates ICE Foundation rules is considered **out of scope**
for the ICE ecosystem.

---

## What ICE Foundation Is Not

ICE Foundation is **not**:

- An engine
- A runtime
- A framework
- A library
- A product
- A documentation site

It contains **no business logic**, **no execution code**, and **no implementation details**.

---

## Core Responsibilities

ICE Foundation is responsible for:

- Defining the canonical terminology of ICE
- Establishing domain boundaries and dependency rules
- Governing plugin and application models
- Declaring architectural invariants
- Publishing RFCs and formal specifications
- Recording irreversible architectural decisions (ADR)

All other ICE repositories **must conform** to ICE Foundation.

---

## Repository Structure

This repository contains:

- `rfc/`  
  Architectural RFCs that define ICE concepts, rules, and evolution

- `specs/`  
  Formal specifications for manifests, lifecycles, and capability models

- `invariants/`  
  Non-negotiable architectural laws and forbidden patterns

- `decisions/`  
  Architectural Decision Records (ADR) explaining irreversible choices

- `glossary.md`  
  Canonical definitions of ICE terminology

---

## Governance Model

ICE Foundation follows a **deliberate and conservative governance model**.

- RFCs are additive and versioned
- Breaking changes require explicit justification
- Invariants are not modified lightly
- Stability is prioritized over convenience

This repository evolves slower than the rest of the ecosystem by design.

---

## Relationship to Other ICE Repositories

- **ICE Foundat**
