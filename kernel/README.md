# YAI Kernel (K-1)

## Role

`kernel/` is the privileged subsystem of YAI OS substrate.

It owns only kernel-grade primitives:
- boot/handoff core integration
- authority root
- containment root
- process/thread core
- scheduler core
- memory core
- VFS/filesystem core
- IPC core
- security/capability/audit core
- container kernel primitives
- kernel lifecycle
- kernel state and registries
- syscall/ABI surface

## Explicitly Out of Kernel

The following are not kernel responsibilities and must stay in userspace/system services:
- orchestration logic
- workflow logic
- graph engine
- data engine
- governance service logic
- rich policy engine logic
- provider logic
- daemon business/runtime logic
- knowledge subsystem logic
- application-facing runtime surfaces
- workspace semantics

## Cutover Strategy

This repository uses aggressive root-level rebuild for the kernel path:
- do not refactor `runtime/` in place
- build canonical root-level structure first (`boot/`, `kernel/`, `sys/`, `user/`)
- treat existing `runtime/` code only as migration source
- migrate only components that pass kernel-grade ownership checks

## Ownership Seed (first migration map)

Potential migration candidates into kernel primitives:
- from current runtime/governance areas: authority, containment, dispatch hooks, enforcement hooks, grants hooks, lifecycle, session core, vault core
- from `lib/platform`: fs/os/uds low-level parts
- from protocol: only low-level ABI/control contract payload surfaces

Explicit non-kernel migration targets:
- workspace/local semantics
- orchestration high-level control
- graph materialization/query summary engines
- rich data evidence/store engines
- providers and knowledge services
- daemon concrete service logic
- high-level mesh/network service logic

## Next Step

K-2 completed: see `kernel/PRIMITIVE_OWNERSHIP_MATRIX.md`.

K-3 completed.

K-4 completed: see `kernel/KERNEL_STATE_REGISTRY_CORE.md` and `kernel/PRIMITIVE_OWNERSHIP_MATRIX.md`.

K-5 completed: see `kernel/KERNEL_SESSION_ADMISSION_MODEL.md` and `kernel/include/yai/kernel/session.h`.

K-6 completed: see `kernel/KERNEL_CONTAINMENT_GOVERNANCE.md` and `kernel/include/yai/kernel/containment.h`.

K-7 completed: see `kernel/KERNEL_POLICY_GRANTS_CORE.md`, `kernel/include/yai/kernel/grants.h`, and `kernel/include/yai/kernel/policy.h`.

K-8 completed: see `kernel/KERNEL_LIFECYCLE_CORE.md` and `kernel/lifecycle/`.

Next: C-1 container canonical definition.
