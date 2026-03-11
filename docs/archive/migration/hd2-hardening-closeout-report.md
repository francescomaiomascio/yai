# HD-2 Hardening Closeout Report

Date: 2026-03-09
Scope: `law` + `yai`

## 1. Embedded hardening results

- Default embedded export now excludes `transitional/domain-family-seed`.
- Embedded contract profile aligned to `runtime-consumer.v4`.
- `embedded/law/README.md` is generated as a runtime-contract marker and preserved on sync.
- Export summaries now derive bridge status from publish-layer manifests.

## 2. Transitional dependence status

- `yai` runtime transitional lookup is now opt-in via `YAI_LAW_ENABLE_TRANSITIONAL_SEED=1`.
- `yai` embed sync transitional payload inclusion is now opt-in via `YAI_LAW_INCLUDE_TRANSITIONAL_SEED=1`.
- `law` export transitional payload inclusion is now opt-in via `LAW_EXPORT_INCLUDE_TRANSITIONAL_SEED=1`.
- Residual transitional material remains in canonical `law/transitional/` as compatibility archive and is not part of the default runtime-facing surface.

## 3. Runtime semantic cleanup

- Domain-loader comments and behavior now explicitly frame transitional seed as non-default bridge.
- Mapping/debug labels now surface `compat_domain_id` to reduce old `event -> domain` mental model ambiguity.
- Compliance loader comments clarify legacy-shape handling as non-primary compatibility path.

## 4. Validation pass

Executed checks:

- `tools/bin/yai-law-compat-check` -> OK
- `tests/unit/law/run_law_unit_tests.sh` -> OK
- `tests/integration/law_resolution/run_law_resolution_smoke.sh` -> OK
- `python3 tools/validate/validate_publish_surface.py` (`law`) -> OK
- `python3 tools/validate/validate_manifests.py` (`law`) -> OK

Note:

- `tools/bin/law-validate` still includes a legacy assumption for `domains/D*` and fails after six-layer migration. This is tracked as non-blocking validator debt.

## 5. Closeout verdict

The convergence cycle can be considered closed for the current hardening scope:

- Canonical publish/export contract is tighter.
- Embedded runtime surface is cleaner and bridge usage is explicit opt-in.
- Runtime code path messaging is less legacy-ambiguous.
- Contract and resolution checks are green on primary runtime path.

Residual non-blocking debt:

- Update or split legacy aggregate validator (`tools/bin/law-validate`) to fully match six-layer canonical topology.
