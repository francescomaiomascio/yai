# Law Embedding Flow

## Before

`yai` consumed law mostly through `deps/law` mirror layout.
That model is now transitional only.

## Now

`yai` consumes a generated embedded law surface:

- canonical law repo: `../law`
- local runtime-facing surface: `embedded/law`

## Commands

```bash
# sync exported law surface from canonical law repo
./tools/bin/yai-law-embed-sync

# validate embedded law shape and compatibility
./tools/bin/yai-law-compat-check
```

## Notes

- `deps/law` may still exist for transition compatibility.
- do not treat `deps/law` as the future architecture.
- do not author normative source directly in `embedded/law`; regenerate it from canonical law.
