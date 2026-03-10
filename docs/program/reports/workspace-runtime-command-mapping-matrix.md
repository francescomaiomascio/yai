---
id: RPT-WSV-2-MAPPING-MATRIX
status: active
owner: runtime-cli-sdk-law
effective_date: 2026-03-10
source_of_truth:
  - lib/core/session/session.c
  - /Users/francescomaiomascio/Developer/YAI/cli/src/parse/parse.c
  - /Users/francescomaiomascio/Developer/YAI/cli/src/help/help.c
  - /Users/francescomaiomascio/Developer/YAI/sdk/include/yai_sdk/workspace.h
  - /Users/francescomaiomascio/Developer/YAI/sdk/include/yai_sdk/graph.h
  - /Users/francescomaiomascio/Developer/YAI/sdk/include/yai_sdk/data.h
  - /Users/francescomaiomascio/Developer/YAI/sdk/include/yai_sdk/knowledge.h
---

# Workspace Runtime Command Mapping Matrix (WSV-2)

Disposition legend:
- `canonical-ready`
- `canonical-via-alias`
- `fallback-only`
- `promote-next`
- `runtime-only`
- `deprecate-path`

| runtime command id | current runtime availability | current CLI exposure | current SDK exposure | canonical CLI target path | canonical family | disposition | action required | follow-up owner |
|---|---|---|---|---|---|---|---|---|
| `yai.workspace.create` | yes (direct dispatch) | yes (`ws create`) | no const/helper | `yai ws create` | lifecycle | canonical-ready | keep canonical | WSV-3 CLI docs/help sync |
| `yai.workspace.open` | yes (direct dispatch) | no direct `ws open` | no const/helper | `yai ws open` | lifecycle | promote-next | add parser/help/renderer mapping | WSV-3 CLI |
| `yai.workspace.set` | yes | yes (`ws set`) | const (`YAI_SDK_CMD_WORKSPACE_SET`) + bind helper | `yai ws set` | lifecycle | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.switch` | yes | yes (`ws switch`) | switch helper (context) | `yai ws switch` (alias to `set`) | lifecycle | canonical-via-alias | document alias=set; keep behavior identical | WSV-3 CLI |
| `yai.workspace.current` | yes | yes (`ws current`) | no const/helper | `yai ws current` | lifecycle | canonical-ready | add SDK const/helper | WSV-4 SDK |
| `yai.workspace.status` | yes | yes (`ws status`) | const + helper | `yai ws status` | lifecycle | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.inspect` | yes | yes (`ws inspect`) | const | `yai ws inspect` | lifecycle | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.unset` | yes | yes (`ws unset`) | const + unbind helper | `yai ws unset` | lifecycle | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.clear` | yes | yes (`ws clear`) | clear binding helper only | `yai ws clear` | lifecycle | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.reset` | yes | yes (`ws reset`) | no const/helper | `yai ws reset` | lifecycle | canonical-ready | add SDK const/helper | WSV-4 SDK |
| `yai.workspace.destroy` | yes | yes (`ws destroy`) | no const/helper | `yai ws destroy` | lifecycle | canonical-ready | add SDK const/helper | WSV-4 SDK |
| `yai.workspace.domain_get` | yes | yes (`ws domain get`) | no const/helper | `yai ws domain get` | domain | canonical-via-alias | canonicalize to nested grammar | WSV-3 CLI + WSV-5 law |
| `yai.workspace.domain.get` | yes | no direct | no | `yai ws domain get` | domain | deprecate-path | keep internal compatibility only | WSV-3 CLI + WSV-5 law |
| `yai.workspace.domain_set` | yes | yes (`ws domain set`) | no | `yai ws domain set` | domain | canonical-via-alias | canonical nested grammar; keep runtime id | WSV-3 CLI + WSV-5 law |
| `yai.workspace.domain.set` | yes | no direct | no | `yai ws domain set` | domain | deprecate-path | compatibility only; remove from canonical docs | WSV-5 law + WSV-6 docs |
| `yai.workspace.policy_attach` | yes | yes (`ws policy attach`) | const | `yai ws policy attach` | policy | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.policy_activate` | yes | yes (`ws policy activate`) | const | `yai ws policy activate` | policy | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.policy_detach` | yes | yes (`ws policy detach`) | const | `yai ws policy detach` | policy | canonical-ready | keep canonical | WSV-3/WSV-4 |
| `yai.workspace.policy_dry_run` | yes | yes (`ws policy dry-run`) | const | `yai ws policy dry-run` | policy | canonical-via-alias | hyphenated CLI grammar stays canonical | WSV-3 CLI + WSV-5 law |
| `yai.workspace.policy_effective` | yes | yes (`ws policy effective`) | no const/helper | `yai ws policy effective` | policy | canonical-ready | add SDK const/helper | WSV-4 SDK |
| `yai.workspace.policy.attach` | yes | no direct | no | `yai ws policy attach` | policy | deprecate-path | keep runtime compat only | WSV-5 law |
| `yai.workspace.policy.detach` | yes | no direct | no | `yai ws policy detach` | policy | deprecate-path | keep runtime compat only | WSV-5 law |
| `yai.workspace.policy.effective` | yes | no direct | no | `yai ws policy effective` | policy | deprecate-path | keep runtime compat only | WSV-5 law |
| `yai.workspace.debug_resolution` | yes | yes (`ws debug resolution`) | no const/helper | `yai ws debug resolution` | debug | canonical-via-alias | canonical nested grammar | WSV-3 CLI + WSV-5 law |
| `yai.workspace.debug.resolution` | yes | no direct | no | `yai ws debug resolution` | debug | deprecate-path | runtime compat only | WSV-5 law |
| `yai.workspace.graph.summary` | yes | no direct | const (`YAI_SDK_CMD_WORKSPACE_GRAPH_SUMMARY`) | `yai ws graph summary` | graph | promote-next | add CLI subcommand and renderer route | WSV-3 CLI |
| `yai.workspace.graph.workspace` | yes | no direct | no | `yai ws graph workspace` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.graph.governance` | yes | no direct | no | `yai ws graph governance` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.graph.decision` | yes | no direct | no | `yai ws graph decision` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.graph.evidence` | yes | no direct | no | `yai ws graph evidence` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.graph.authority` | yes | no direct | no | `yai ws graph authority` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.graph.artifact` | yes | no direct | no | `yai ws graph artifact` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.graph.lineage` | yes | no direct | no | `yai ws graph lineage` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.graph.recent` | yes | no direct | no | `yai ws graph recent` | graph | promote-next | add CLI subcommand | WSV-3 CLI |
| `yai.workspace.query` + `events` | yes (family via query) | no direct `ws query` grammar | query const + data/knowledge family constants | `yai ws data events` | data | promote-next | add canonical subcommand over query substrate | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.query` + `evidence` | yes | no direct | query const + data family | `yai ws data evidence` | data | promote-next | canonical wrapper over query | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.query` + `governance` | yes | no direct | query const + data family | `yai ws data governance` | data | promote-next | canonical wrapper over query | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.query` + `authority` | yes | no direct | query const + data family | `yai ws data authority` | data | promote-next | canonical wrapper over query | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.query` + `artifact` | yes | no direct | query const + data family | `yai ws data artifacts` | data | promote-next | canonical wrapper over query | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.query` + `enforcement` | yes | no direct | query const + data family | `yai ws data enforcement` | data | promote-next | canonical wrapper over query | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.query` + `transient` | yes | no direct | query const + knowledge family | `yai ws knowledge transient` | knowledge | promote-next | canonical wrapper over query | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.query` + `memory` | yes | no direct | query const + knowledge family | `yai ws knowledge memory` | knowledge | promote-next | canonical wrapper over query | WSV-3 CLI + WSV-4 SDK |
| `yai.workspace.governance.list` | yes | no direct | no | `yai ws data governance` | data | canonical-via-alias | allow as internal runtime alias | WSV-3 CLI + WSV-5 law |
| `yai.workspace.events.tail` | yes | no direct | no | `yai ws data events` / `yai ws db tail` | data/db | canonical-via-alias | choose primary target in WSV-3 (`data events`) | WSV-3 CLI |
| `yai.workspace.evidence.list` | yes | no direct | no | `yai ws data evidence` | data | canonical-via-alias | internal alias only | WSV-3 CLI + WSV-5 law |
| `yai.workspace.authority.list` | yes | no direct | no | `yai ws data authority` | data | canonical-via-alias | internal alias only | WSV-3 CLI + WSV-5 law |
| `yai.workspace.artifacts.list` | yes | no direct | no | `yai ws data artifacts` | data | canonical-via-alias | internal alias only | WSV-3 CLI + WSV-5 law |
| `yai.workspace.enforcement.status` | yes | no direct | no | `yai ws data enforcement` | data | canonical-via-alias | internal alias only | WSV-3 CLI + WSV-5 law |
| `yai.workspace.lifecycle.model` | yes (query family=lifecycle) | no direct | no | `yai ws recovery status` | recovery | runtime-only | expose later if semantics stabilized | later runtime + WSV-3 |
| `yai.workspace.lifecycle.status` | yes | no direct | no | `yai ws recovery status` | recovery | promote-next | canonical wrapper + renderer | WSV-3 CLI |
| `yai.workspace.lifecycle.maintain` | yes | no direct | no | `yai ws recovery load` | recovery | runtime-only | needs UX contract before exposure | later runtime wave |
| `yai.workspace.run` | yes | yes (`ws run`) | const | `yai ws run` | exec/workspace | canonical-ready | keep canonical | WSV-3 docs/help |
| `yai.workspace.prompt_context` | yes | yes (`ws prompt-context`/`prompt-token`) | no | `yai ws inspect` adjunct | inspect | runtime-only | keep utility, not family anchor | WSV-6 docs |
| *(composed)* `status+inspect` recovery fields | yes (indirect in payload) | yes via existing commands | yes via inspect/status models | `yai ws recovery status` | recovery | promote-next | add command composition now | WSV-3 CLI |
| *(composed)* `open` (+lifecycle status) | yes | partial (`ws set/switch`, no `ws open`) | partial | `yai ws recovery reopen` | recovery | canonical-via-alias | map to `workspace.open` | WSV-3 CLI |
| *(composed)* query+store refs | yes (inspect/query) | no direct | partial (query const) | `yai ws db status` | db | promote-next | implement CLI composition using inspect/status/query | WSV-3 CLI |
| *(composed)* inspect refs (`*_store_ref`) | yes | no direct | no typed helper | `yai ws db stores` | db | promote-next | add CLI renderer and SDK typed reader | WSV-3 CLI + WSV-4 SDK |
| *(composed)* status+inspect binding fields | yes | no direct | no typed helper | `yai ws db bindings` | db | promote-next | compose from `binding_status/runtime_capabilities/read_path` | WSV-3 CLI + WSV-4 SDK |
| *(composed)* query family inventory | yes | no direct | constants only | `yai ws db classes` | db | fallback-only | start as synthetic projection from query families | WSV-3 CLI |
| *(composed)* query counts | yes | no direct | constants only | `yai ws db count` | db | fallback-only | start with query-backed aggregate | WSV-3 CLI |
| *(composed)* `events.tail` + query families | yes | no direct | constants only | `yai ws db tail` | db | fallback-only | short-term: query-based tail; later dedicated ID | WSV-3 CLI + later runtime |

