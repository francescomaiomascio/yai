# Workspace Governance Apply Walkthrough

This walkthrough demonstrates object-to-workspace apply semantics with dry-run.

## Preconditions

- runtime running (`yai up`)
- active workspace (`yai ws set <ws-id>`)
- object discoverable in governable registry

## Flow

1. Dry-run compatibility preview

```bash
yai ws policy dry-run enterprise.ecohmedia.digital-outbound.review-gate
```

2. Attach object

```bash
yai ws policy attach enterprise.ecohmedia.digital-outbound.review-gate
```

3. Activate attachment (idempotent if already active)

```bash
yai ws policy activate enterprise.ecohmedia.digital-outbound.review-gate
```

4. Inspect effective contribution

```bash
yai ws inspect
yai ws policy effective
yai ws debug resolution
```

5. Detach

```bash
yai ws policy detach enterprise.ecohmedia.digital-outbound.review-gate
```

## Expected interpretation

- `dry-run` shows `eligibility_result`, `compatibility_result`, `conflict_summary`.
- `attach` shows `attachment_state` and `activation_state`.
- `policy effective` and `debug resolution` include updated attachments and stack.
- `detach` removes object from active workspace attachments.
