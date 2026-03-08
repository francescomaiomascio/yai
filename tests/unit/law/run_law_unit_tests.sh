#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
OUT_DIR="$ROOT/build/test/unit_law"
mkdir -p "$OUT_DIR"

LAW_SRCS=$(find "$ROOT/lib/law" -type f -name '*.c' | sort)
CFLAGS='-Wall -Wextra -std=c11 -O2'
INCLUDES="-I$ROOT/include -I$ROOT/include/yai"

for t in \
  test_manifest_loader \
  test_domain_loader \
  test_compliance_loader \
  test_discovery \
  test_resolution \
  test_precedence \
  test_effective_stack
 do
  cc $CFLAGS $INCLUDES "$ROOT/tests/unit/law/${t}.c" $LAW_SRCS -o "$OUT_DIR/$t"
  "$OUT_DIR/$t"
 done

echo "law_unit_tests: ok"
