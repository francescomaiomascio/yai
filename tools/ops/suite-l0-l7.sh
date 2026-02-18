#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
exec "$ROOT/tools/ops/suite/levels/l0-l7.sh" "$@"
