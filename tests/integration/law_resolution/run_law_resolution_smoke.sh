#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
OUT_DIR="$ROOT/build/test/integration_law_resolution"
mkdir -p "$OUT_DIR"

LAW_SRCS=$(find "$ROOT/lib/law" -type f -name '*.c' | sort)
CFLAGS='-Wall -Wextra -std=c11 -O2'
INCLUDES="-I$ROOT/include -I$ROOT/include/yai"

for t in test_d1_resolution test_d8_resolution test_cross_domain_resolution; do
  cc $CFLAGS $INCLUDES "$ROOT/tests/integration/law_resolution/${t}.c" $LAW_SRCS -o "$OUT_DIR/$t"
  "$OUT_DIR/$t"
done

echo "law_resolution_smoke: ok"
