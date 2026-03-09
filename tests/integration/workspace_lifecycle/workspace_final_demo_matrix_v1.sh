#!/usr/bin/env bash
set -euo pipefail

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"

# This script composes the final matrix from existing validated scenarios.
"$REPO/tests/integration/workspace_lifecycle/workspace_session_binding_contract_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_inspect_surfaces_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_real_flow_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_scientific_flow_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_digital_flow_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_hostile_path_baseline_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_isolation_guards_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_negative_paths_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_governed_vertical_slice_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_governance_apply_semantics_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_review_approval_gate_v1.sh"
"$REPO/tests/integration/workspace_lifecycle/workspace_agent_safe_boundaries_v1.sh"

echo "workspace_final_demo_matrix_v1: ok"
