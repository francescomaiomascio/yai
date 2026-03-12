#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
BIN="$ROOT_DIR/build/bin/yai-containerd"

if [[ ! -x "$BIN" ]]; then
  echo "missing binary: $BIN" >&2
  exit 1
fi

TMP_HOME="$(mktemp -d /tmp/yai-containerd-test.XXXXXX)"
trap 'rm -rf "$TMP_HOME"' EXIT
export HOME="$TMP_HOME"

CID="sys-smoke"

"$BIN" create "$CID" managed
"$BIN" initialize "$CID"
"$BIN" open "$CID"
"$BIN" attach "$CID" 1001

OUT_ACTIVE="$("$BIN" show "$CID")"
echo "$OUT_ACTIVE" | grep -q "lifecycle=active"
echo "$OUT_ACTIVE" | grep -q "session_bound=1"
echo "$OUT_ACTIVE" | grep -q "policy_view=1 grants_view=1"

"$BIN" recover "$CID"
OUT_RECOVERY="$("$BIN" show "$CID")"
echo "$OUT_RECOVERY" | grep -q "lifecycle=recovery"
echo "$OUT_RECOVERY" | grep -q "recovery-flags=1"

"$BIN" seal "$CID"
"$BIN" destroy "$CID"
OUT_DESTROYED="$("$BIN" show "$CID")"
echo "$OUT_DESTROYED" | grep -q "lifecycle=destroyed"

echo "containerd smoke: ok"
