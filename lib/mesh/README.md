# Mesh Implementation Domain (Canonical)

`lib/mesh/` is the canonical distributed topology domain of the unified YAI
system.

Canonical subdomains:

- `discovery/`
- `enrollment/`
- `identity/`
- `peer_registry/`
- `membership/`
- `coordination/`
- `awareness/`
- `transport/`
- `containment/`
- `conflict/`
- `replay/`
- `internal/`

Boundary rules:

- mesh is a first-class domain, not daemon-only networking helpers
- protocol transport framing remains under `lib/protocol/`
- edge-local runtime behavior remains under `lib/edge/`
