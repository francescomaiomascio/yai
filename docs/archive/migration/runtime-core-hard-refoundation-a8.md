# A8 - Runtime Core Hard Refoundation

A8 refounds the runtime core topology from legacy `core` accumulation to the
canonical governed runtime domain.

## Canonical runtime domain

- `lib/runtime/authority/`
- `lib/runtime/enforcement/`
- `lib/runtime/workspace/`
- `lib/runtime/session/`
- `lib/runtime/dispatch/`
- `lib/runtime/lifecycle/`
- `lib/runtime/policy/`
- `lib/runtime/grants/`
- `lib/runtime/containment/`
- `lib/runtime/internal/`

## Cutover actions

- Moved implementation sources from `lib/core/*` to `lib/runtime/*`.
- Updated build source topology to compile runtime from `lib/runtime/*`.
- Switched runtime implementation includes to `yai/runtime/*`.
- Promoted `include/yai/runtime/*` as primary header surface.
- Kept `include/yai/core/*` as compatibility shim headers.

## Transitional compatibility

- `include/yai/core/*` remains available as shim namespace during migration.
- legacy docs/reports may still mention `core`; canonical naming is `runtime`.
