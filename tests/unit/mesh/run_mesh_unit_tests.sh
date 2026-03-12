#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
OUT_DIR="$ROOT/build/test/unit_mesh"
mkdir -p "$OUT_DIR"

cc -Wall -Wextra -std=c11 -O2 \
  -I"$ROOT/include" -I"$ROOT/include/yai" \
  "$ROOT/tests/unit/mesh/test_mesh_minimal.c" \
  "$ROOT/lib/network/topology/peer_identity.c" \
  "$ROOT/lib/network/topology/reachability.c" \
  "$ROOT/lib/network/topology/membership.c" \
  "$ROOT/lib/network/discovery/discovery.c" \
  "$ROOT/lib/network/mesh/mesh_runtime.c" \
  "$ROOT/lib/network/mesh/coordination.c" \
  "$ROOT/lib/network/overlay/session_state.c" \
  "$ROOT/lib/network/overlay/replay_state.c" \
  "$ROOT/lib/network/overlay/conflict_ordering.c" \
  "$ROOT/lib/network/mesh/containment.c" \
  "$ROOT/lib/network/discovery/enrollment.c" \
  -o "$OUT_DIR/mesh_unit_tests"

"$OUT_DIR/mesh_unit_tests"
echo "mesh_unit_tests: ok"
