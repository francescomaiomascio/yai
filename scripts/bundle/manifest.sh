#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 9 ]; then
  echo "usage: $0 <stage_dir> <bundle_version> <core_version> <core_git_sha> <cli_ref> <cli_git_sha> <specs_git_sha> <os> <arch>" >&2
  exit 1
fi

STAGE_DIR="$1"
BUNDLE_VERSION="$2"
CORE_VERSION="$3"
CORE_GIT_SHA="$4"
CLI_REF="$5"
CLI_GIT_SHA="$6"
SPECS_GIT_SHA="$7"
PLATFORM_OS="$8"
PLATFORM_ARCH="$9"

BIN_DIR="$STAGE_DIR/bin"
OUT_MANIFEST="$STAGE_DIR/manifest.json"

for req in "$STAGE_DIR" "$BUNDLE_VERSION" "$CORE_VERSION" "$CORE_GIT_SHA" "$CLI_REF" "$CLI_GIT_SHA" "$SPECS_GIT_SHA" "$PLATFORM_OS" "$PLATFORM_ARCH"; do
  if [ -z "$req" ]; then
    echo "ERROR: manifest requires non-empty fields" >&2
    exit 1
  fi
done

if [ ! -d "$BIN_DIR" ]; then
  echo "ERROR: missing bin directory in stage: $BIN_DIR" >&2
  exit 1
fi

required_bins=(yai-boot yai-root-server yai-kernel yai-engine yai)
for bin in "${required_bins[@]}"; do
  if [ ! -f "$BIN_DIR/$bin" ]; then
    echo "ERROR: missing required binary for manifest: $BIN_DIR/$bin" >&2
    exit 1
  fi
done

hash_file() {
  local f="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$f" | awk '{print $1}'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$f" | awk '{print $1}'
  else
    echo "ERROR: no sha256 tool found (sha256sum/shasum)" >&2
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

CREATED_AT="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"

{
  printf '{\n'
  printf '  "bundle": {\n'
  printf '    "bundle_version": "%s",\n' "$BUNDLE_VERSION"
  printf '    "created_at": "%s",\n' "$CREATED_AT"
  printf '    "os": "%s",\n' "$PLATFORM_OS"
  printf '    "arch": "%s"\n' "$PLATFORM_ARCH"
  printf '  },\n'
  printf '  "core": {\n'
  printf '    "version": "%s",\n' "$CORE_VERSION"
  printf '    "git_sha": "%s"\n' "$CORE_GIT_SHA"
  printf '  },\n'
  printf '  "cli": {\n'
  printf '    "ref": "%s",\n' "$CLI_REF"
  printf '    "git_sha": "%s"\n' "$CLI_GIT_SHA"
  printf '  },\n'
  printf '  "specs": {\n'
  printf '    "path": "deps/yai-specs",\n'
  printf '    "git_sha": "%s"\n' "$SPECS_GIT_SHA"
  printf '  },\n'
  printf '  "artifacts": [\n'

  first=1
  while IFS= read -r file; do
    [ -f "$file" ] || continue
    rel="bin/$(basename "$file")"
    sha="$(hash_file "$file")"
    size="$(file_size "$file")"
    if [ "$first" -eq 0 ]; then
      printf ',\n'
    fi
    printf '    {"path": "%s", "sha256": "%s", "size": %s}' "$rel" "$sha" "$size"
    first=0
  done < <(find "$BIN_DIR" -maxdepth 1 -type f | sort)

  printf '\n  ]\n'
  printf '}\n'
} > "$OUT_MANIFEST"

echo "Generated manifest: $OUT_MANIFEST"
