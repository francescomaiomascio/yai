# A10 - Mesh Topology Refoundation

A10 establishes `mesh/` as a canonical system domain for governed distributed
operation.

## Canonical mesh implementation topology

- `lib/mesh/discovery/`
- `lib/mesh/enrollment/`
- `lib/mesh/identity/`
- `lib/mesh/peer_registry/`
- `lib/mesh/membership/`
- `lib/mesh/coordination/`
- `lib/mesh/awareness/`
- `lib/mesh/transport/`
- `lib/mesh/containment/`
- `lib/mesh/conflict/`
- `lib/mesh/replay/`
- `lib/mesh/internal/`

## Canonical mesh public headers

- `include/yai/mesh/discovery.h`
- `include/yai/mesh/enrollment.h`
- `include/yai/mesh/identity.h`
- `include/yai/mesh/peer_registry.h`
- `include/yai/mesh/membership.h`
- `include/yai/mesh/coordination.h`
- `include/yai/mesh/awareness.h`
- `include/yai/mesh/transport.h`
- `include/yai/mesh/containment.h`
- `include/yai/mesh/conflict.h`
- `include/yai/mesh/replay.h`

## Boundary model

- `mesh` models governed distributed topology and peer-state semantics.
- `edge` models subordinate runtime behavior local to a node.
- `runtime` models sovereign owner-side runtime authority and core behavior.
- `protocol` models transport framing/contract encoding, not mesh membership
  semantics.

## Operational readiness intent

This topology is explicitly structured to host stale-peer handling, reconnect,
overlap/conflict handling, quarantine containment, replay, and degraded-mode
behavior in upcoming slices.
