#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
DIST_ROOT="${DIST_ROOT:-$ROOT_DIR/dist}"
BIN_DIST="${BIN_DIST:-$DIST_ROOT/bin}"
BUNDLE_ROOT="$DIST_ROOT/bundle"
STAGE_ROOT="$BUNDLE_ROOT/stage"
OUT_ROOT="$BUNDLE_ROOT/out"

EXPECTED_BINS=(
  yai-boot
  yai-root-server
  yai-kernel
  yai-engine
)

if [ ! -d "$BIN_DIST" ]; then
  echo "ERROR: missing $BIN_DIST. Run 'make dist' first." >&2
  exit 1
fi

for bin in "${EXPECTED_BINS[@]}"; do
  if [ ! -f "$BIN_DIST/$bin" ]; then
    echo "ERROR: missing dist binary $BIN_DIST/$bin. Run 'make dist'." >&2
    exit 1
  fi
done

if [ ! -d "$ROOT_DIR/deps/yai-specs" ]; then
  echo "ERROR: missing deps/yai-specs. Run 'git submodule update --init --recursive'." >&2
  exit 1
fi

REPO_COMMIT="$(git -C "$ROOT_DIR" rev-parse --short=12 HEAD)"
if [ -n "${BUNDLE_VERSION:-}" ]; then
  VERSION="$BUNDLE_VERSION"
else
  VERSION="dev-$(date -u +%Y%m%d)-$REPO_COMMIT"
fi

UNAME_S="$(uname -s)"
case "$UNAME_S" in
  Linux) PLATFORM_OS="linux" ;;
  Darwin) PLATFORM_OS="macos" ;;
  *) PLATFORM_OS="$(echo "$UNAME_S" | tr '[:upper:]' '[:lower:]')" ;;
esac
PLATFORM_ARCH="$(uname -m)"

BUNDLE_NAME="yai-bundle-${VERSION}-${PLATFORM_OS}-${PLATFORM_ARCH}"
STAGE_DIR="$STAGE_ROOT/$BUNDLE_NAME"

rm -rf "$STAGE_DIR"
mkdir -p "$STAGE_DIR/bin" "$OUT_ROOT"

for bin in "${EXPECTED_BINS[@]}"; do
  cp "$BIN_DIST/$bin" "$STAGE_DIR/bin/$bin"
done

mkdir -p "$STAGE_DIR/specs"
(
  cd "$ROOT_DIR/deps/yai-specs"
  tar --exclude='.git' -cf - .
) | (
  cd "$STAGE_DIR/specs"
  tar -xf -
)

for f in LICENSE NOTICE THIRD_PARTY_NOTICES.md DATA_POLICY.md; do
  if [ -f "$ROOT_DIR/$f" ]; then
    cp "$ROOT_DIR/$f" "$STAGE_DIR/$f"
  fi
done

cat > "$STAGE_DIR/README_BUNDLE.md" <<BUNDLE_README
# YAI Bundle

This bundle contains runtime binaries and a pinned snapshot of contracts from \`deps/yai-specs\`.

## Verify integrity

Use \`sha256sum -c SHA256SUMS\` on Linux or \`shasum -a 256 -c SHA256SUMS\` on macOS.
BUNDLE_README

SPECS_COMMIT="$(git -C "$ROOT_DIR" submodule status -- deps/yai-specs | awk '{print $1}' | sed 's/^[-+]//')"
if [ -z "$SPECS_COMMIT" ]; then
  SPECS_COMMIT="unknown"
fi

bash "$ROOT_DIR/scripts/bundle/manifest.sh" \
  "$STAGE_DIR" \
  "$VERSION" \
  "yai" \
  "$REPO_COMMIT" \
  "$SPECS_COMMIT" \
  "$PLATFORM_OS" \
  "$PLATFORM_ARCH"

(
  cd "$STAGE_DIR"
  if command -v sha256sum >/dev/null 2>&1; then
    find . -type f ! -name SHA256SUMS -print | sort | sed 's#^./##' | while read -r f; do
      sha256sum "$f"
    done > SHA256SUMS
  elif command -v shasum >/dev/null 2>&1; then
    find . -type f ! -name SHA256SUMS -print | sort | sed 's#^./##' | while read -r f; do
      shasum -a 256 "$f"
    done > SHA256SUMS
  else
    echo "ERROR: sha256 tool not found (sha256sum/shasum)." >&2
    exit 1
  fi
)

TAR_OUT="$OUT_ROOT/${BUNDLE_NAME}.tar.gz"
ZIP_OUT="$OUT_ROOT/${BUNDLE_NAME}.zip"
MANIFEST_OUT="$OUT_ROOT/${BUNDLE_NAME}.manifest.json"
SHA_OUT="$OUT_ROOT/${BUNDLE_NAME}.SHA256SUMS"

tar -C "$STAGE_ROOT" -czf "$TAR_OUT" "$BUNDLE_NAME"
(
  cd "$STAGE_ROOT"
  zip -qr "$ZIP_OUT" "$BUNDLE_NAME"
)

cp "$STAGE_DIR/manifest.json" "$MANIFEST_OUT"
cp "$STAGE_DIR/SHA256SUMS" "$SHA_OUT"

echo "Bundle output:"
echo "  $TAR_OUT"
echo "  $ZIP_OUT"
echo "  $MANIFEST_OUT"
echo "  $SHA_OUT"
