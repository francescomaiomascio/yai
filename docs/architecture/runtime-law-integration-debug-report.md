# Runtime Law Integration Debug Report

> Historical report: superseded by active boundary/consumption references in:
> - `docs/architecture/law-consumption-model.md`
> - `docs/architecture/embedded-law-surface.md`
> - `docs/architecture/law-runtime-convergence-audit.md`
>
> Use this file as historical analysis only, not as primary runtime reference.
>
> Post-cutover update: `deps/law` is retired from active runtime and tooling paths.

Date: 2026-03-08
Scope: first law-native integration pass in `yai`

## Executive verdict

`yai` is now law-aware in runtime flow, but current implementation is an early operational scaffold.

- Strong: loader/classifier/discovery/resolver modules are present, build passes, tests run.
- Weak: discovery and stack build are still hardcoded around digital/scientific seed; semantic depth is limited.
- High risk: documentation and tooling are still split between new `embedded/law` model and old `deps/law` references.

## Classification by area

### Root/docs identity

- `README.md`: **Approved as scaffold**
- `LAW_COMPATIBILITY.md`: **Approved as skeleton**
- `docs/README.md`: **Approved as scaffold**
- `docs/architecture/law-consumption-model.md`: **Approved as skeleton**
- `docs/architecture/embedded-law-surface.md`: **Approved as skeleton**

Finding:
- Narrative is directionally correct, but large doc surfaces still reference `deps/law` as active normative anchor.

### embedded/law

Status: **Duplicated** + **Needs cleanup**

Evidence:
- `embedded/law` contains 391 files (94 markdown, 296 json).
- `deps/law` has 163 files, so embedded surface is currently larger than legacy mirror.
- Embedded includes many README/documentation artifacts; boundary is not yet “minimal runtime artifact surface”.

Judgment:
- Current embedded is closer to a structured copy than a compiled runtime package.

### deps/law

Status: **Legacy-contaminated**

Judgment: **still operationally relevant**

Evidence:
- Build/test/docs still reference `deps/law` heavily (`Makefile`, `tools/dev`, many docs under `docs/platform`, `docs/program`, `docs/interfaces`).
- Runtime loader prefers `embedded/law` but explicitly falls back to `deps/law`.

### include/yai/law and lib/law

- `include/yai/law/`: **Approved as scaffold**
- `lib/law/loader`: **Approved as scaffold**
- `lib/law/classification`: **Approved as scaffold**
- `lib/law/discovery`: **Approved as scaffold**
- `lib/law/resolution`: **Fragile**
- `lib/law/mapping`: **Approved as skeleton**
- `lib/law/debug`: **Approved as skeleton**

Key finding:
- Architecture split is clean, but resolver internals are mostly deterministic handcrafted logic for digital/scientific seed (not yet generic policy engine over full manifest/schema semantics).

### Enforcement handoff

Status: **Approved as scaffold**

Evidence:
- Handoff is wired in `lib/core/session/session.c` via `yai_law_resolve_control_call(...)`.
- Effects map into runtime reply paths with rationale/evidence trace.

Gap:
- Effect mapping is coarse and control-call centric; broader runtime execution surfaces are not yet integrated.

### Tests

- `tests/unit/law/`: **Approved as scaffold**
- `tests/integration/law_resolution/`: **Approved as scaffold**

Coverage judgment:
- Good smoke baseline for digital/scientific seed path.
- Insufficient for ambiguity/fallback/conflict complexity and cross-domain compliance interactions.
- Mostly happy-path and binary decision assertions.

### Docs contamination (major)

Status: **Legacy-contaminated**

Evidence:
- Extensive `deps/law` references across `docs/platform/**`, `docs/program/**`, `docs/interfaces/**`, and generated alignment docs.
- Conflicts with new narrative that runtime consumption is embedded-first.

## Fault lines

1. Embedded surface not yet minimal
- Too much payload duplication, too many markdown artifacts.

2. Dual normative path in docs/tooling
- `embedded/law` declared primary, while large portions still enforce/pin `deps/law` language.

3. Resolver semantics not yet data-driven enough
- Core behavior still encodes domain logic branches directly in runtime code.

## Bucket classification summary

### Approved and stable
- Module boundaries for law consumer subsystem.
- Build/test wiring and basic runtime integration.

### Approved as scaffold
- Loader/classifier/discovery/resolution pipeline shape.
- digital/scientific seed integration smoke paths.

### Needs refoundation before verticalization
- Embedded export packaging model (compile/minimize surface).
- Docs/program lineage still tied to legacy law pathing.

### Needs mass verticalization
- Resolver semantics beyond digital/scientific seed.
- Data-driven policy composition from manifests instead of hardcoded branches.

### Legacy contamination to remove
- `deps/law` references in docs/program/interfaces and helper tools.

### Narrative ambiguity to close
- One authoritative consumption model only: embedded-first, explicit legacy policy.

## Readiness for next block

Ready now:
- digital/scientific seed runtime verticalization continuation.

Not ready yet:
- broad domain expansion before resolving embedded-minimization and dual-path docs contamination.

Recommended order:
1. Embedded surface minimization + export hardening
2. Docs/tooling decontamination from `deps/law` in active paths
3. Resolver genericity improvements (domain/compliance composition via data)
4. Add non-happy-path tests (ambiguity/conflict/fallback)
