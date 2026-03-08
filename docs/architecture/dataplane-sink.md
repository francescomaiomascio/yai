# Dataplane Sink (Out of Scope)

This tranche does not implement dataplane persistence, graph storage, query APIs, or decision/evidence databases.

Current in-scope boundary in `yai`:

- law-native classification/discovery/resolution
- effect mapping to enforcement
- evidence envelope and resolution trace preparation

Any durable storage/export/query work is deferred to a dedicated dataplane tranche.
