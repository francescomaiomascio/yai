# C-1 Workspace -> Container Migration Map

Migration sources:
- `include/yai/runtime/workspace.h`
- `lib/runtime/workspace/*`
- `include/yai/runtime/local/*`
- `lib/runtime/local/*`

Canonical target:
- `include/yai/container/*`
- `lib/container/*`

Rules:
- workspace is legacy-only naming
- container is the canonical operational domain
- kernel containment/session/grants roots remain kernel-owned
