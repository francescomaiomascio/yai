#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
PIN_FILE="$ROOT/deps/yai-cli.ref"
YAI_CLI_REPO="${YAI_CLI_REPO:-https://github.com/francescomaiomascio/yai-cli.git}"
YAI_CLI_BRANCH="${YAI_CLI_BRANCH:-main}"

resolve_from_sha() {
  local sha="$1"
  if ! echo "$sha" | grep -Eq '^[0-9a-f]{40}$'; then
    echo "ERROR: YAI_CLI_SHA must be a 40-hex commit SHA" >&2
    exit 1
  fi
  if ! git ls-remote "$YAI_CLI_REPO" | awk '{print $1}' | grep -qx "$sha"; then
    echo "ERROR: YAI_CLI_SHA ($sha) not found in remote refs for $YAI_CLI_REPO" >&2
    exit 1
  fi
  printf "%s\n" "$sha"
}

resolve_from_tag() {
  local tag="$1"
  local sha=""
  sha="$(git ls-remote --tags "$YAI_CLI_REPO" "refs/tags/${tag}^{}" | awk '{print $1}' | head -n1 || true)"
  if [ -z "$sha" ]; then
    sha="$(git ls-remote --tags "$YAI_CLI_REPO" "refs/tags/${tag}" | awk '{print $1}' | head -n1 || true)"
  fi
  if [ -z "$sha" ]; then
    echo "ERROR: could not resolve YAI_CLI_TAG=$tag in $YAI_CLI_REPO" >&2
    exit 1
  fi
  printf "%s\n" "$sha"
}

resolve_from_branch() {
  local branch="$1"
  local sha=""
  sha="$(git ls-remote --heads "$YAI_CLI_REPO" "refs/heads/$branch" | awk '{print $1}' | head -n1 || true)"
  if [ -z "$sha" ]; then
    echo "ERROR: could not resolve YAI_CLI_BRANCH=$branch in $YAI_CLI_REPO" >&2
    exit 1
  fi
  printf "%s\n" "$sha"
}

main() {
  local resolved=""
  if [ -n "${YAI_CLI_SHA:-}" ]; then
    resolved="$(resolve_from_sha "$YAI_CLI_SHA")"
  elif [ -n "${YAI_CLI_TAG:-}" ]; then
    resolved="$(resolve_from_tag "$YAI_CLI_TAG")"
  else
    resolved="$(resolve_from_branch "$YAI_CLI_BRANCH")"
  fi

  if ! echo "$resolved" | grep -Eq '^[0-9a-f]{40}$'; then
    echo "ERROR: resolved yai-cli reference is not a 40-hex SHA: $resolved" >&2
    exit 1
  fi

  printf "cli_sha=%s\n" "$resolved" > "$PIN_FILE"
  printf "%s\n" "$resolved"
}

main "$@"
