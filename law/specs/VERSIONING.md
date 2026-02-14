# Specs Versioning & Compatibility

Rules:
- Backward compatible changes: additive only (new optional fields / new commands gated by capability).
- Breaking changes: new major version (v2).
- Deprecation: keep for >=1 major, mark explicitly in schema/docs, provide migration notes.

Runtime behavior:
- Clients must send protocol version and capabilities during handshake.
- Servers must reject incompatible major versions with deterministic error codes.
