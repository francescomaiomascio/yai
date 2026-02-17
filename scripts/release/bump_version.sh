#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<USAGE
Usage: $(basename "$0") <major|minor|patch|X.Y.Z> [--commit] [--tag]

Examples:
  $(basename "$0") patch
  $(basename "$0") minor --commit
  $(basename "$0") 0.2.0 --commit --tag
USAGE
}

if [ "$#" -lt 1 ]; then
  usage
  exit 1
fi

if [ "${1:-}" = "-h" ] || [ "${1:-}" = "--help" ]; then
  usage
  exit 0
fi

BUMP="$1"
shift || true
DO_COMMIT=0
DO_TAG=0

while [ "$#" -gt 0 ]; do
  case "$1" in
    --commit) DO_COMMIT=1 ;;
    --tag) DO_TAG=1 ;;
    -h|--help) usage; exit 0 ;;
    *) echo "Unknown arg: $1" >&2; usage; exit 1 ;;
  esac
  shift || true
done

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
cd "$ROOT"

if [ ! -f VERSION ]; then
  echo "ERROR: VERSION file not found in $ROOT" >&2
  exit 1
fi
if [ ! -f CHANGELOG.md ]; then
  echo "ERROR: CHANGELOG.md not found in $ROOT" >&2
  exit 1
fi

CURRENT="$(tr -d "[:space:]" < VERSION)"
if ! echo "$CURRENT" | grep -Eq "^[0-9]+\.[0-9]+\.[0-9]+$"; then
  echo "ERROR: VERSION is not semver: $CURRENT" >&2
  exit 1
fi

IFS=. read -r MAJ MIN PAT <<< "$CURRENT"

case "$BUMP" in
  major) NEW="$((MAJ + 1)).0.0" ;;
  minor) NEW="$MAJ.$((MIN + 1)).0" ;;
  patch) NEW="$MAJ.$MIN.$((PAT + 1))" ;;
  *)
    if echo "$BUMP" | grep -Eq "^[0-9]+\.[0-9]+\.[0-9]+$"; then
      NEW="$BUMP"
    else
      echo "ERROR: bump must be major|minor|patch or X.Y.Z" >&2
      exit 1
    fi
    ;;
esac

if [ "$NEW" = "$CURRENT" ]; then
  echo "ERROR: new version equals current version ($CURRENT)" >&2
  exit 1
fi

if grep -Eq "^## \[$NEW\]" CHANGELOG.md; then
  echo "ERROR: CHANGELOG already contains version $NEW" >&2
  exit 1
fi

DATE_UTC="$(date -u +%Y-%m-%d)"

printf "%s\n" "$NEW" > VERSION

TMP="$(mktemp)"
awk -v v="$NEW" -v d="$DATE_UTC" '
  BEGIN { inserted=0 }
  {
    print $0
    if (inserted==0 && $0 ~ /^## \[?[Uu]nreleased\]?$/) {
      print ""
      print "## [" v "] - " d
      print ""
      print "- TODO: summarize release changes."
      inserted=1
    }
  }
  END {
    if (inserted==0) {
      print ""
      print "## [" v "] - " d
      print ""
      print "- TODO: summarize release changes."
    }
  }
' CHANGELOG.md > "$TMP"
mv "$TMP" CHANGELOG.md

echo "Updated VERSION: $CURRENT -> $NEW"
echo "Updated CHANGELOG: added section [${NEW}]"

if [ "$DO_COMMIT" -eq 1 ]; then
  git add VERSION CHANGELOG.md
  git commit -m "chore(release): bump version to v${NEW}"
  echo "Created commit for v${NEW}"
fi

if [ "$DO_TAG" -eq 1 ]; then
  git tag -a "v${NEW}" -m "Release v${NEW}"
  echo "Created annotated tag v${NEW}"
fi
