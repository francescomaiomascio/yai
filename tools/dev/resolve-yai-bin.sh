#!/usr/bin/env bash
set -euo pipefail

# Resolve canonical YAI binaries for the unified runtime topology.
# Usage:
#   yai_resolve_bin "<repo_root>"      -> yai CLI path
#   yai_resolve_core_bin "<repo_root>" -> yai-core path

yai_resolve_core_bin() {
  local root="${1:-}"

  if [[ -n "${CORE_BIN:-}" && -x "${CORE_BIN:-}" ]]; then
    echo "$CORE_BIN"
    return 0
  fi
  if [[ -n "${YAI_CORE_BIN:-}" && -x "${YAI_CORE_BIN:-}" ]]; then
    echo "$YAI_CORE_BIN"
    return 0
  fi

  if [[ -n "$root" && -x "$root/build/bin/yai-core" ]]; then
    echo "$root/build/bin/yai-core"
    return 0
  fi

  if command -v yai-core >/dev/null 2>&1; then
    command -v yai-core
    return 0
  fi

  # Legacy fallback (compatibility only).
  if [[ -x "$HOME/.yai/artifacts/yai/bin/yai-core" ]]; then
    echo "$HOME/.yai/artifacts/yai/bin/yai-core"
    return 0
  fi

  return 1
}

yai_resolve_bin() {
  local root="${1:-}"

  if [[ -n "${BIN:-}" && -x "${BIN:-}" ]]; then
    echo "$BIN"
    return 0
  fi
  if [[ -n "${YAI_BIN:-}" && -x "${YAI_BIN:-}" ]]; then
    echo "$YAI_BIN"
    return 0
  fi

  if [[ -n "$root" && -x "$root/build/bin/yai" ]]; then
    echo "$root/build/bin/yai"
    return 0
  fi

  if command -v yai >/dev/null 2>&1; then
    command -v yai
    return 0
  fi

  # Legacy fallback (compatibility only).
  if [[ -x "$HOME/.yai/artifacts/yai/bin/yai" ]]; then
    echo "$HOME/.yai/artifacts/yai/bin/yai"
    return 0
  fi

  return 1
}
