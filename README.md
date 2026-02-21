# YAI — Sovereign Intelligence Runtime
_Acronym: “YAI Ain’t Intelligence”_

> **Status: Pre-release (0.x).**  
> YAI is under active development. Interfaces may change. Treat upgrades as deliberate operations.

YAI is a **sovereign runtime for intelligence**: a governed execution stack where AI systems run with **deterministic boundaries, auditable state, and explicit authority**—not opaque side-effects.

**Start here:** [Docs](#documentation) · [Specs & Contracts](#specs--contracts) · [Build](#get-started) · [Security](#security) · [License](#license)

---

## Why YAI

Modern AI delivers capability, but too often without governance: decisions that cannot be traced, state that cannot be proven, and effects that cannot be constrained.

YAI is built to make **intelligence operational**—measurable, accountable, and reproducible—so you can deploy AI as infrastructure, not as a leap of faith.

---

## What YAI Is

YAI brings up a vertical runtime stack designed for **controlled intelligence execution**:

- **Boot** — machine bring-up and environment verification
- **Root Plane** — global authority surface and control coordination
- **Kernel (L1)** — workspace isolation, policy enforcement, session authority
- **Engine (L2)** — deterministic execution and gated external effects
- **Mind (L3)** — higher orchestration (emerging line)

This repository contains the **foundation runtime** (Boot/Root/Kernel/Engine) and the operational tooling to verify and package it.

---

## Principles

YAI treats governance as a first-class system property:

- **Determinism over improvisation** — execution paths are bounded and repeatable
- **Auditability over opacity** — state transitions are observable and attributable
- **Explicit authority over implicit power** — permissions are declared, verified, and enforced
- **Contracts over drift** — behavior is defined by specs, not by “whatever happens”

---

## Get Started

### Option A — Bundle (recommended when available)
Official bundles will be published via GitHub **Releases** once the first pre-release package is cut.

### Option B — Build from source (today)
Clone the repo and build the runtime locally.

- Installation, verification, and operational runbooks live in: `docs/`
- Tooling used by CI and local verification lives in: `tools/`

> If you’re evaluating YAI right now: start from `docs/` and follow the runbooks.  
> If something cannot be reproduced, treat it as a defect.

---

## Specs & Contracts

The source of truth for behavior lives in **`deps/yai-specs`**.

Specs are not “documentation”; they are **normative contracts**.  
The runtime implements these contracts—**and must remain aligned**. When alignment breaks, it is treated as a defect.

---

## Documentation

- `docs/` — architecture notes, runbooks, guides, operational procedures
- `data/` — datasets used for local tests/ops (see `DATA_POLICY.md`)
- `tools/` — verification and gate tooling used in CI and release pipelines

---

## Releases

**Pre-release note:** Releases may be empty while the project stabilizes.

- For now, use **tags** as the primary version marker.
- When releases are enabled, each bundle will ship with a manifest + checksums to support reproducible deployment.

---

## Security

See `SECURITY.md` for disclosure and handling policy.

---

## License

Apache-2.0. See `LICENSE`, `NOTICE`, and `THIRD_PARTY_NOTICES.md`.
