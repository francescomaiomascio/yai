#!/usr/bin/env bash
set -euo pipefail

# Resolve embedded law surface root consumed by runtime-facing tooling.
yai_resolve_law_embed_root() {
  local root="${1:-}"

  if [[ -n "${YAI_LAW_EMBED_ROOT:-}" && -d "${YAI_LAW_EMBED_ROOT:-}" ]]; then
    echo "$YAI_LAW_EMBED_ROOT"
    return 0
  fi

  if [[ -n "$root" && -d "$root/embedded/law" ]]; then
    echo "$root/embedded/law"
    return 0
  fi

  return 1
}
