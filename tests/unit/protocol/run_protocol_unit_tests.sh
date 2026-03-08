#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
OUT_DIR="$ROOT/build/test/unit_protocol"
LAW_COMPAT_ROOT="${LAW_COMPAT_ROOT:-$ROOT/deps/law}"
mkdir -p "$OUT_DIR"

cc -Wall -Wextra -std=c11 -O2 \
  -I"$ROOT/include" -I"$ROOT/include/yai" \
  -I"$LAW_COMPAT_ROOT/contracts/protocol/include" \
  -I"$LAW_COMPAT_ROOT/contracts/protocol/runtime/include" \
  "$ROOT/tests/unit/protocol/protocol_test.c" \
  -o "$OUT_DIR/protocol_test"

"$OUT_DIR/protocol_test"
