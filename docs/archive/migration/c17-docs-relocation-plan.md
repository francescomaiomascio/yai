# C17 Docs Relocation Plan

## Applied wave (C17)

1. Create canonical spine directories for architecture, guides, runbooks, reference, program, generated, archive.
2. Move `developer` + `developers` content into `guides`/`runbooks`/`reference`.
3. Move `interfaces` into `reference`.
4. Declassify `platform/architecture` into `archive/historical-architecture`.
5. Normalize `program/` branch naming.
6. Move `program/23-runbooks` into `runbooks/operations/program`.
7. Archive historical overviews and migration-only program files.
8. First relocation wave moved 416 tracked documentation files (`git status` rename class `R*`).

## Follow-up wave

- Deep content rewrite and dedup of architecture narratives.
- Link integrity pass for historical documents that still reference old paths.
