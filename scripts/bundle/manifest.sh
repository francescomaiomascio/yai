#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 7 ]; then
  echo "usage: $0 <stage_dir> <bundle_version> <repo_name> <repo_commit> <specs_commit> <os> <arch>" >&2
  exit 1
fi

STAGE_DIR="$1"
BUNDLE_VERSION="$2"
REPO_NAME="$3"
REPO_COMMIT="$4"
SPECS_COMMIT="$5"
PLATFORM_OS="$6"
PLATFORM_ARCH="$7"

BIN_DIR="$STAGE_DIR/bin"
OUT_MANIFEST="$STAGE_DIR/manifest.json"

if [ ! -d "$BIN_DIR" ]; then
  echo "missing bin directory in stage: $BIN_DIR" >&2
  exit 1
fi

hash_file() {
  local f="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$f" | awk '{print $1}'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$f" | awk '{print $1}'
  else
    echo "no sha256 tool found" >&2
    exit 1
  fi
}

file_size() {
  local f="$1"
  if stat -f%z "$f" >/dev/null 2>&1; then
    stat -f%z "$f"
  else
    stat -c%s "$f"
  fi
}

CREATED_UTC="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"

{
  printf '{\n'
  printf '  "bundle_version": "%s",\n' "$BUNDLE_VERSION"
  printf '  "created_utc": "%s",\n' "$CREATED_UTC"
  printf '  "repo": {"name": "%s", "commit": "%s"},\n' "$REPO_NAME" "$REPO_COMMIT"
  printf '  "specs": {"path": "deps/yai-specs", "commit": "%s"},\n' "$SPECS_COMMIT"
  printf '  "platform": {"os": "%s", "arch": "%s"},\n' "$PLATFORM_OS" "$PLATFORM_ARCH"
  printf '  "compat": {"specs_pinned_to_commit": "%s"},\n' "$SPECS_COMMIT"
  printf '  "binaries": [\n'

  first=1
  for f in "$BIN_DIR"/*; do
    [ -f "$f" ] || continue
    name="$(basename "$f")"
    sha="$(hash_file "$f")"
    size="$(file_size "$f")"
    if [ "$first" -eq 0 ]; then
      printf ',\n'
    fi
    printf '    {"name": "%s", "sha256": "%s", "size": %s}' "$name" "$sha" "$size"
    first=0
  done

  printf '\n  ]\n'
  printf '}\n'
} > "$OUT_MANIFEST"

echo "Generated manifest: $OUT_MANIFEST"
