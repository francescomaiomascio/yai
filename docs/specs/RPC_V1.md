# RPC v1

Editorial pointer only.

Canonical sources:

- `law/specs/control/control_plane.v1.json`
- `law/specs/cli/CLI_PUBLIC_INTERFACE.md`
- `law/specs/cli/commands.v1.json`

### `down_ok`
Payload:
- `shutdown` (bool)

### `providers`
Payload:
- `items` (array of ProviderInfo)

### `provider_status`
Payload:
- `active` (ProviderInfo or null)

### `providers_ok`
No payload.

### `events_started`
No payload. Stream follows.

### `error`
Payload:
- `message` (string)
