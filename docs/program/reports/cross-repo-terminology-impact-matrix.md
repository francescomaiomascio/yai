# DX-1 Annex — Cross-Repo Terminology Impact Matrix

Status: active
Owner: ecosystem
Source contract: `docs/architecture/cross-repo-naming-and-terminology-contract.md`

| Concept | Canonical term | Disallowed / legacy variants | Repos affected | Surface types affected | Downstream owner |
|---|---|---|---|---|---|
| Unified runtime | `runtime` / `unified runtime` | `brain runtime`, detached subsystem runtime | yai, law, sdk, cli | README, architecture, status/help | DX-2 |
| Runtime families | `core/exec/data/graph/knowledge` | `core/exec/brain`, umbrella subsystem owners | yai, law, sdk, cli | architecture, pointers, contract docs | DX-2 |
| Workspace boundary | `workspace binding boundary` | workspace as path-only | yai, sdk, cli, law | workspace docs, SDK models, CLI output | DX-3 |
| Active workspace | `active workspace` | generic `current context` without binding semantics | yai, sdk, cli | inspect/status/help | CLI-2, SDK-2 |
| Binding | `workspace binding` | detached attach-stage naming | yai, law, sdk, cli | status, runtime docs, contracts | DX-3 |
| Readiness | `ready` (capability-context aware) | liveness-only interpreted as readiness | yai, sdk, cli | runtime status, inspect, SDK responses | CLI-2, SDK-2 |
| Liveness | `alive` / process liveness | implied full operational readiness | yai, sdk, cli | startup/status help text | CLI-2, SDK-2 |
| Degraded | `degraded` capability | ambiguous partial-ready labels | yai, sdk, cli | status payloads, operator output | CLI-2, SDK-2 |
| Recovery/load | `recovered` / `restored` | implicit startup continuation wording | yai, sdk, cli | workspace runtime docs, inspect | DX-3, CLI-2 |
| Exec ownership | `exec` owns agents/orchestration | orchestration under cognition subsystem | yai, law, sdk, cli | architecture, SDK/CLI command descriptions | DX-2, SDK-1, CLI-1 |
| Knowledge ownership | `knowledge` support family | knowledge as execution owner | yai, law, sdk, cli | docs, models, responses | DX-2, SDK-2 |
| Data ownership | `data` persistence family | data hidden under legacy umbrellas | yai, law, sdk, cli | docs, API/CLI descriptions | DX-2, SDK-2, CLI-2 |
| Graph ownership | `graph` relational truth family | graph under legacy memory/brain ownership | yai, law, sdk, cli | docs, summaries, inspect/output | DX-2, DX-3, CLI-2 |
| Governance targeting | family-aware workspace-bound targeting | detached subsystem-target governance | law, yai, sdk, cli | law docs, runtime docs, SDK/CLI integration docs | DX-2, SDK-3, CLI-3 |
| Runtime entrypoint | canonical runtime entrypoint | legacy subsystem entrypoint language | law, yai, sdk, cli | manifests/docs/help | DX-2, SDK-1, CLI-1 |
| Attachability | workspace-bound attachability | subsystem attach-stage semantics | law, yai, sdk, cli | constraints/docs/walkthroughs | DX-3, SDK-3, CLI-3 |
| Governable object | `governable object` | policy object wording without lifecycle context | law, yai, sdk, cli | law/runtime docs, SDK/CLI guides | DX-3, SDK-3, CLI-3 |
| Primitive | `primitive` (law capability unit) | mixed non-canonical naming per repo | law, yai, sdk, cli | law refs, developer docs, integrations | DX-3 |
| Agent-safe | `agent-safe` governance profile | implicit permissive action language | law, yai, sdk, cli | docs and command guidance | DX-3, SDK-3, CLI-3 |

## Repo Focus Notes

### yai
- Remove legacy topology wording in active runbooks and architecture summaries.
- Keep runtime/startup/status wording aligned with binding/readiness contract.

### law
- Preserve explicit deprecated alias fields for machine compatibility.
- Keep active docs de-authorized from legacy subsystem truth.

### sdk
- Normalize request/response model wording to canonical binding/readiness terms.
- Align examples to workspace-bound capability semantics.

### cli
- Normalize help/status wording to canonical family and readiness semantics.
- Keep operator language consistent with SDK/runtime payload model.
