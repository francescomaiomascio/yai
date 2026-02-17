#!/usr/bin/env bash
set -euo pipefail

YAI_SPECS_REPO="${YAI_SPECS_REPO:-https://github.com/francescomaiomascio/yai-specs.git}"
YAI_CLI_REPO="${YAI_CLI_REPO:-https://github.com/francescomaiomascio/yai-cli.git}"
STRICT_SPECS_HEAD="${STRICT_SPECS_HEAD:-1}"

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
TMP_DIR="$(mktemp -d)"
cleanup() {
  rm -rf "$TMP_DIR"
}
trap cleanup EXIT

short_sha() {
  local sha="${1:-}"
  if echo "$sha" | grep -Eq '^[0-9a-f]{40}$'; then
    printf "%s" "${sha:0:12}"
  else
    printf "%s" "$sha"
  fi
}

print_fix_plan() {
  local expected_sha="$1"
  local yai_pin="$2"
  local yai_cli_pin="$3"
  local short="${expected_sha:0:7}"

  cat <<EOF
[SUMMARY]
  expected_specs_sha : ${expected_sha}
  yai_pin            : ${yai_pin}
  yai_cli_pin        : ${yai_cli_pin}

Fix (required before release):

  export YAI_WORKSPACE="<path-to-your-yai-workspace>"

  yai-cli (bump deps/yai-specs to ${expected_sha})
    cd "\$YAI_WORKSPACE/yai-cli"
    git checkout main && git pull --rebase
    git checkout -b chore/bump-specs-${short}
    git -C deps/yai-specs fetch origin
    git -C deps/yai-specs checkout ${expected_sha}
    git add deps/yai-specs
    git commit -m "chore(specs): bump yai-specs pin to ${short} in yai-cli"
    git push -u origin chore/bump-specs-${short}

  yai (bump deps/yai-specs to ${expected_sha})
    cd "\$YAI_WORKSPACE/yai"
    git checkout main && git pull --rebase
    git checkout -b chore/bump-specs-${short}
    git -C deps/yai-specs fetch origin
    git -C deps/yai-specs checkout ${expected_sha}
    git add deps/yai-specs
    git commit -m "chore(specs): bump yai-specs pin to ${short} in yai"
    git push -u origin chore/bump-specs-${short}
EOF
}

fail() {
  local code="$1"
  local msg="$2"
  local expected_sha="${3:-}"
  local yai_pin="${4:-unknown}"
  local yai_cli_pin="${5:-unknown}"
  echo
  echo "[RESULT] FAIL"
  echo "[REASON] $msg"
  if [ -n "$expected_sha" ] && { [ "$code" -eq 2 ] || [ "$code" -eq 3 ] || [ "$code" -eq 4 ]; }; then
    print_fix_plan "$expected_sha" "$yai_pin" "$yai_cli_pin"
  fi
  echo
  echo "[MACHINE]"
  echo "result=FAIL"
  echo "reason=$msg"
  echo "exit_code=$code"
  echo "yai_pin=$yai_pin"
  echo "yai_cli_pin=$yai_cli_pin"
  if [ -n "$expected_sha" ]; then
    echo "expected_specs_sha=$expected_sha"
  fi
  exit "$code"
}

if [ ! -d "$ROOT/deps/yai-specs/.git" ] && [ ! -f "$ROOT/deps/yai-specs/.git" ]; then
  fail 3 "deps/yai-specs is not a git repo; cannot verify pin"
fi

YAI_SPECS_PIN="$(git -C "$ROOT/deps/yai-specs" rev-parse HEAD 2>/dev/null || true)"
if ! echo "$YAI_SPECS_PIN" | grep -Eq '^[0-9a-f]{40}$'; then
  fail 3 "invalid yai specs pin from deps/yai-specs"
fi

YAI_CLI_MAIN_SHA="$(git ls-remote "$YAI_CLI_REPO" refs/heads/main | awk '{print $1}' | head -n1 || true)"
if ! echo "$YAI_CLI_MAIN_SHA" | grep -Eq '^[0-9a-f]{40}$'; then
  fail 3 "cannot resolve yai-cli main HEAD from $YAI_CLI_REPO"
fi

CLI_TMP="$TMP_DIR/yai-cli"
git clone --depth 1 "$YAI_CLI_REPO" "$CLI_TMP" >/dev/null 2>&1
YAI_CLI_SPECS_PIN="$(git -C "$CLI_TMP" rev-parse HEAD:deps/yai-specs 2>/dev/null || true)"
if ! echo "$YAI_CLI_SPECS_PIN" | grep -Eq '^[0-9a-f]{40}$'; then
  fail 3 "could not resolve yai-cli specs pin from gitlink deps/yai-specs"
fi

SPECS_HEAD="$(git ls-remote "$YAI_SPECS_REPO" refs/heads/main | awk '{print $1}' | head -n1 || true)"
if ! echo "$SPECS_HEAD" | grep -Eq '^[0-9a-f]{40}$'; then
  fail 3 "cannot resolve yai-specs main HEAD from $YAI_SPECS_REPO"
fi

CHECK_TMP="$TMP_DIR/specs-check"
git init -q "$CHECK_TMP"
git -C "$CHECK_TMP" remote add origin "$YAI_SPECS_REPO"
if ! git -C "$CHECK_TMP" fetch --depth 1 origin "$YAI_SPECS_PIN" >/dev/null 2>&1; then
  fail 3 "yai specs pin $YAI_SPECS_PIN is not reachable in $YAI_SPECS_REPO" "$SPECS_HEAD" "$YAI_SPECS_PIN" "$YAI_CLI_SPECS_PIN"
fi
if ! git -C "$CHECK_TMP" cat-file -e "${YAI_SPECS_PIN}^{commit}" >/dev/null 2>&1; then
  fail 3 "yai specs pin $YAI_SPECS_PIN is not a valid commit in $YAI_SPECS_REPO" "$SPECS_HEAD" "$YAI_SPECS_PIN" "$YAI_CLI_SPECS_PIN"
fi

echo "[CHECK]"
echo "  yai_pin            : $(short_sha "$YAI_SPECS_PIN")"
echo "  yai_cli_pin        : $(short_sha "$YAI_CLI_SPECS_PIN")"
echo "  yai_cli_main_head  : $(short_sha "$YAI_CLI_MAIN_SHA")"
echo "  yai_specs_main_head: $(short_sha "$SPECS_HEAD")"
echo "  strict_specs_head  : $STRICT_SPECS_HEAD"

if [ "$YAI_SPECS_PIN" != "$YAI_CLI_SPECS_PIN" ]; then
  fail 2 "pin mismatch between yai and yai-cli" "$SPECS_HEAD" "$YAI_SPECS_PIN" "$YAI_CLI_SPECS_PIN"
fi

if [ "$STRICT_SPECS_HEAD" = "1" ] && [ "$YAI_SPECS_PIN" != "$SPECS_HEAD" ]; then
  fail 4 "strict mode enabled and pin is not yai-specs/main HEAD" "$SPECS_HEAD" "$YAI_SPECS_PIN" "$YAI_CLI_SPECS_PIN"
fi

echo
echo "[RESULT] PASS"
echo "[REASON] aligned specs pins"
echo
echo "[MACHINE]"
echo "result=PASS"
echo "reason=aligned specs pins"
echo "exit_code=0"
echo "yai_pin=$YAI_SPECS_PIN"
echo "yai_cli_pin=$YAI_CLI_SPECS_PIN"
echo "expected_specs_sha=$SPECS_HEAD"
echo "PASS: yai and yai-cli specs pins are aligned and valid."
