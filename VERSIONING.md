# Versioning Policy

## Scope

This policy applies to the `yai` core runtime repository.

## Scheme

`yai` follows Semantic Versioning: `MAJOR.MINOR.PATCH`.

- `MAJOR`: breaking runtime behavior or compatibility guarantees
- `MINOR`: backward-compatible features or additive behavior
- `PATCH`: backward-compatible fixes, hardening, docs, or maintenance

## Specs Pinning Requirement

Every runtime release must declare the pinned `deps/yai-specs` compatibility target
(tag or commit) used during verification.

Release notes should include:

- `yai` release version
- pinned `deps/yai-specs` commit/tag
- compatibility impact summary

## Breaking Change Criteria

A change is breaking if it requires consumers/operators to change behavior or tooling,
including protocol surface behavior, required flags, runtime compatibility envelope,
or workspace/process lifecycle guarantees.

## Compatibility Link

Compatibility guarantees and support matrix are maintained in `COMPATIBILITY.md`.

## License

This policy is part of the Apache-2.0 licensed repository. See `LICENSE` and `NOTICE`.
