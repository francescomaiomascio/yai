# YAI Core

`yai-core` is the canonical repository that binds **YAI Law** to the **Kernel runtime**.

Law is authoritative and lives under `law/`.
Kernel is subordinate and lives under `kernel/`.

---

## Repository Layout

yai-core/
├── law/ # Axioms, invariants, boundaries, specs, formal models (authority)
├── kernel/ # C runtime implementation (L1 enforcement)
└── scripts/ # Verification scripts (TLC + kernel build)

---

## Canonical Authority (Law)

The following are normative and authoritative:

- `law/axioms/`
- `law/invariants/`
- `law/boundaries/`
- `law/specs/`
- `law/formal/`

If runtime behavior conflicts with these, the runtime is wrong.

---

## Kernel Runtime (L1)

The kernel enforces:

- the canonical state machine (L1)
- authority gating
- transition trace evidence
- vault layout constraints (L0)

Kernel code lives in `kernel/` and is bound to Law via:

- `law/formal/KERNEL_LAW_BINDING.md`
- `law/formal/spec_map.md`

---

## Verification (Red Button)

Single command to validate Law ↔ Kernel coherence:

```bash
cd yai-core
./scripts/verify-law-kernel.sh
```

This runs:

- TLC model checking (quick + deep)
- Kernel build

---

## Non-Goals

yai-core is not:

- a product repo
- an application runtime
- a UI or studio repo

It is the authority + enforcement core only.

---

## Governance

This repository is governed by YAI Law under `law/`.
Any change to runtime behavior that affects axioms, invariants, or boundaries
must update Law first.
