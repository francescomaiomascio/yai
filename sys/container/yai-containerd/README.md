# yai-containerd

`yai-containerd` is the canonical userspace system service for container domain management.

Responsibilities:
- create/open/attach/initialize/recover/seal/destroy container domains
- publish container runtime surfaces
- mediate requests through kernel-owned primitives

Non-responsibilities:
- kernel privileged containment roots
- high-level policy composition/governance/compliance engines
- orchestration brain
- daemon control plane ownership
