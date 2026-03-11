#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SDK="$ROOT/../sdk"
CLI="$ROOT/../cli"

run() {
  echo "[final-matrix] $*"
  "$@"
}

run make -C "$ROOT" -j4
run make -C "$ROOT" governance-check
run tests/unit/governance/run_governance_unit_tests.sh
run tests/integration/governance/run_governance_resolution_smoke.sh

run make -C "$SDK" -j4
run "$SDK"/tools/sh/check_api_boundaries.sh
run "$SDK"/build/tests/workspace_smoke
run "$SDK"/build/tests/sdk_smoke

run make -C "$CLI" -j4
run "$CLI"/tests/integration/workspace_output_guardrail.sh

if [[ "${RUN_SOCKET_SCENARIOS:-0}" == "1" ]]; then
  run "$ROOT"/tests/integration/workspace/workspace_session_binding_contract.sh
  run "$ROOT"/tests/integration/workspace/workspace_inspect_surfaces.sh
  run "$ROOT"/tests/integration/workspace/workspace_real_flow.sh
  run "$ROOT"/tests/integration/workspace/workspace_scientific_flow.sh
  run "$ROOT"/tests/integration/workspace/workspace_digital_flow.sh
  run "$ROOT"/tests/integration/workspace/workspace_hostile_path_baseline.sh
  run "$ROOT"/tests/integration/workspace/workspace_isolation_guards.sh
  run "$ROOT"/tests/integration/workspace/workspace_negative_paths.sh
else
  echo "[final-matrix] socket scenarios skipped (set RUN_SOCKET_SCENARIOS=1 to enable)"
fi

echo "[final-matrix] ok"
