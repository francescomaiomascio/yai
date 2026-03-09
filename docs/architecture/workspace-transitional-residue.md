# Workspace Transitional Residue (WS-6)

This note classifies what is still transitional on the workspace path after WS-6.

## Active canonical path

- command grammar: `law/registry/commands*.json`
- runtime consumer: `yai` workspace/session/law resolver path
- operator surface: `cli` `ws` commands (`current/status/inspect/domain/policy/debug/run`)

## Residual bridge/tolerated items

- dotted command aliases (`yai.workspace.domain.get`, `yai.workspace.policy.effective`, etc.) are still accepted in runtime for compatibility with earlier scripts.
- internal compatibility `domain_id` mapping (`D*`) is still present in discovery output as bridge metadata.
- lifecycle/legacy workspace ops in registry (`ws_*`) remain outside the active workspace normative path.

## Not on active path

- legacy `deps/law`-driven discovery semantics (runtime primary path is embedded law).
- historical docs flagged as superseded.

## Planned removal candidates (post-WS-6)

- remove dotted workspace command aliases once downstream scripts migrate to canonical underscore IDs.
- reduce compatibility `D*` exposure from user-facing outputs after full runtime genericity completion.
- prune non-active workspace ops from default help exposure if not used by operator workflows.
