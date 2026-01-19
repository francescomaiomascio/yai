# Security Policy

## Purpose

This document defines the **security posture** of this repository
within the ICE ecosystem.

The purpose of this policy is to:

- define the operational security scope of this project
- clarify what constitutes a security issue
- establish reporting and disclosure expectations
- preserve alignment with ICE Foundation invariants

This repository contains **executable code and/or operational logic**.
Security concerns therefore include both **conceptual** and **implementation-level** risks.

---

## Relationship to ICE Foundation

This project is **downstream of ICE Foundation**.

As such:

- ICE Foundation defines axioms and structural invariants
- This repository must comply with those constraints
- No implementation decision may violate Foundation authority

Any security issue that implies a violation of Foundation axioms
is considered **critical**, regardless of exploitability.

---

## Security Scope

Security concerns for this repository include:

- unauthorized execution or capability escalation
- violation of authority or governance constraints
- bypass of traceability or accountability mechanisms
- nondeterministic or unreconstructable execution paths
- unsafe handling of external inputs or providers
- incorrect enforcement of permissions or boundaries
- vulnerabilities in execution, IPC, or integration surfaces

Both **design flaws** and **implementation defects** are in scope.

---

## Out of Scope

The following are **not** handled in this repository:

- vulnerabilities in third-party providers or models
- infrastructure or cloud configuration issues
- operating system or hardware security
- vulnerabilities in unrelated downstream products

Such issues must be reported to the appropriate owner.

---

## Supported Versions

This project does not guarantee long-term security support
for all historical versions.

Security fixes apply to:

- the current main branch
- active development branches, when applicable

Users are expected to track the latest stable state.

---

## Reporting a Security Issue

Security issues should be reported by opening a **GitHub Issue**
in this repository.

Reports must include:

- a clear description of the issue
- affected components or files
- security impact (authority, execution, data, governance)
- steps to reproduce, if applicable

If the issue involves **active exploitation**, clearly mark it as such.

---

## Disclosure Policy

There is **no private disclosure channel** by default.

ICE favors **transparent and public resolution** unless:

- active exploitation is demonstrated
- coordinated disclosure is explicitly requested

Maintainers may temporarily restrict discussion
to prevent harm, but transparency is the default.

---

## Security Definition (ICE Context)

Within ICE, security is defined as:

> The preservation of explicit authority, traceable execution,
> and governable behavior over time.

Any behavior that undermines these properties
is considered a security failure,
even if no traditional exploit is involved.

---

## Canonical Status

This policy is authoritative for this repository.

It complements, and does not override,
the axioms, invariants, and governance rules
defined in ICE Foundation.
