# A10 Migration Marker - Mesh Topology Canonicalization

Canonical mesh domains now live under `lib/mesh/` with mirrored public surface
under `include/yai/mesh/`.

Boundary lock:

- no new mesh semantics should be introduced under `lib/daemon/` or `lib/exec/`
  when they belong to canonical mesh subdomains.
