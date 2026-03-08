#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
YAI="$ROOT/build/bin/yai"

if [[ ! -x "$YAI" ]]; then
  make -C "$ROOT" yai >/dev/null
fi

"$YAI" exec-probe
