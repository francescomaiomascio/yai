#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
YAI_CORE="$ROOT/build/bin/yai-core"

if [[ ! -x "$YAI_CORE" ]]; then
  make -C "$ROOT" yai-core >/dev/null
fi

"$YAI_CORE" --brain-check
