#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
OUT_ROOT="$ROOT/build/test/brain"
OBJ_DIR="$OUT_ROOT/obj"
BIN_DIR="$OUT_ROOT/bin"
mkdir -p "$OBJ_DIR" "$BIN_DIR"

if [[ ! -f "$OBJ_DIR/lib/brain/lifecycle/brain_lifecycle.o" ]]; then
  "$ROOT/tests/unit/brain/run_brain_unit_tests.sh" >/dev/null
fi

DAEMON_BIN="$BIN_DIR/yai-mind-compat"
if [[ ! -x "$DAEMON_BIN" ]]; then
  mapfile -t OBJS < <(find "$OBJ_DIR/lib/brain" -type f -name '*.o' | sort)
  cc -Wall -Wextra -std=c11 -O2 -I"$ROOT/include" -I"$ROOT/include/yai" \
    "$ROOT/cmd/legacy/yai-mind/main.c" "${OBJS[@]}" -o "$DAEMON_BIN" -lm
fi

mapfile -t OBJS < <(find "$OBJ_DIR/lib/brain" -type f -name '*.o' | sort)

for t in test_runtime_primary test_mind_daemon_smoke; do
  cc -Wall -Wextra -std=c11 -O2 -I"$ROOT/include" -I"$ROOT/include/yai" \
    "$ROOT/tests/integration/core_brain/$t.c" "${OBJS[@]}" -o "$BIN_DIR/$t" -lm
  if [[ "$t" == "test_mind_daemon_smoke" ]]; then
    YAI_MIND_BIN="$DAEMON_BIN" "$BIN_DIR/$t"
  else
    "$BIN_DIR/$t"
  fi
done
