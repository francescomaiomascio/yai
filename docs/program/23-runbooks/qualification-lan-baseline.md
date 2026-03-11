# Qualification LAN Baseline Runbook (QW-1)

## Goal

Run the first qualification wave in LAN/trusted-network mode with canonical command grammar and reusable test layout.

## Prerequisites

- Repo: `yai`
- Binaries buildable: `yai`, `yai-daemon`
- Local host supports UNIX sockets and standard temp directories

Build once:

```bash
make yai yai-daemon
```

## Qualification Layout

- `tests/integration/qualification/lib/`
- `tests/integration/qualification/fixtures/bologna-mini/`
- `tests/integration/qualification/lan/`

LAN wave runner:

```bash
tests/integration/qualification/lan/run_qw1_lan_wave_v1.sh
```

Optional evidence root override:

```bash
QW1_EVIDENCE_ROOT=/tmp/qw1-evidence tests/integration/qualification/lan/run_qw1_lan_wave_v1.sh
```

## LAN Wave Tests

Precheck:

1. `ql_lan_command_contract_v1.sh`

LAN baseline scenarios:

1. `ql_lan_enroll_attach_emit_v1.sh`
2. `ql_lan_three_peers_same_workspace_v1.sh`
3. `ql_lan_peer_offline_replay_v1.sh`
4. `ql_lan_distinct_assets_v1.sh`
5. `ql_lan_overlap_assets_v1.sh`
6. `ql_lan_backlog_drain_v1.sh`

Each script prints `<name>: ok` on success.

## Scenario Matrix (QW-1)

1. Command contract gate
Validate canonical owner-side runtime command IDs and inspect/query/graph summary surfaces.
Expected: workspace create/set, source enroll/attach, query family reads, graph summary all `status=ok`.

2. Enroll/attach/emit baseline
Validate owner ingest bridge and source-plane baseline flow.
Expected: enroll + attach + emit path accepted in owner runtime.

3. Three peers same workspace
Validate multi-peer LAN membership baseline.
Expected: peer count and workspace membership/read-model counters are coherent.

4. Peer offline replay
Validate repeat-delivery semantics for a peer contribution stream in LAN baseline.
Expected: repeated emit submissions remain accepted and peer visibility remains coherent.

5. Distinct assets coverage
Validate non-overlapping coverage in source read model.
Expected: `coverage_scope_count>=2`, overlap count remains 0.

6. Overlap assets visibility
Validate overlap/conflict pressure visibility in source-plane read surfaces.
Expected: overlap-related state is visible and non-ambiguous.

7. Backlog drain
Validate burst ingest baseline and post-burst visibility.
Expected: multi-emit burst remains accepted and coverage/read-model visibility remains coherent.

## Expected Outcomes

- owner ingest path accepts enroll/attach/emit baseline
- one workspace is fed by multiple peers (3-peer baseline)
- peer replay-like repeated emit path remains semantically coherent in LAN baseline
- distinct coverage shows no overlap pressure
- overlap scenario is visible in source read model/conflict surfaces
- backlog-style burst ingest remains visible and non-ambiguous

## Fixture Set

`tests/integration/qualification/fixtures/bologna-mini/` includes:

- `peer-a-performance/` (CSV)
- `peer-b-programmazione/` (CSV)
- `peer-c-documentale/` (PDF-like fixtures)

This fixture set is intentionally small but non-trivial and coverage-oriented.

## Troubleshooting

- If socket bind/listen fails, rerun with clean temp home and ensure no stale socket path.
- If a LAN script fails, rerun the single script first, then the full wave.
- Keep owner/peer logs from temp directories when debugging intermittent replay/backlog failures.

## Evidence Collection Contract

QW-1 runner writes reusable evidence pack under:

- `tests/integration/qualification/evidence/<run-id>/`

Artifacts:

- `meta.txt`: run id, start/end timestamps
- `results.tsv`: per-step status, duration, log pointer
- `<script>.log`: full output for precheck and each LAN scenario

Use this evidence pack as baseline input for QW-2..QW-6.

## Next Wave Boundary

After QW-1 passes, move to secure peering qualification (`QW-2`) reusing:

- command contract (`docs/developer/qualification-command-contract.md`)
- qualification layout
- helper layer
- fixture discipline

Do not rename command grammar between LAN and peering waves.
