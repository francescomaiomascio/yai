# Container System Service Layer

`sys/container/` hosts the container system service plane.

Canonical service: `yai-containerd`.

Boundaries:
- kernel owns privileged containment/admission/grants roots
- container manager consumes kernel primitives to manage container domains
- CLI, orchestration, and daemon consume container surfaces; they do not replace container manager ownership
