# Specs Registry

This is the authoritative list of runtime contracts.

| Domain | Spec / Schema | Implemented by | Consumed by | Notes |
|---|---|---|---|---|
| protocol | protocol.h + transport.h + yai_protocol_ids.h | kernel + engine | cli + mind | envelope, handshake |
| control | control_plane.v1.json | kernel | cli | control plane commands |
| graph | graph.v1.json | engine(storage_gate) | mind | RPC graph ops |
| providers | providers.v1.json | engine(provider_gate) | mind | external network boundary |
| vault | vault_abi.json + yai_vault_abi.h | kernel | cli + engine | ABI verification |
| compliance | compliance.context.v1.json | engine | mind | required context |
