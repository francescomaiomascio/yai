# Qualification Integration Layout

QW-1 introduces the qualification layout and LAN baseline wave.

- `lan/`: executable qualification scripts for local/trusted network baseline.
- `peering/`: reserved for secure peering wave (QW-2).
- `scale/`: reserved for scale simulation wave.
- `realflow/`: reserved for real-flow qualification wave.
- `fixtures/`: shared test datasets and sample assets.
- `lib/`: shared helpers (`qualification_common.sh`, `qualification_asserts.sh`).

Entrypoint for QW-1 LAN wave:

- `tests/integration/qualification/lan/run_lan_wave.sh`

QW-1 composition:

- precheck: `lan_command_contract.sh` (canonical command contract gate)
- LAN scenarios (6):
  - `lan_enroll_attach_emit.sh`
  - `lan_three_peers_same_workspace.sh`
  - `lan_peer_offline_replay.sh`
  - `lan_distinct_assets.sh`
  - `lan_overlap_assets.sh`
  - `lan_backlog_drain.sh`

Evidence output:

- default root: `tests/integration/qualification/evidence/<run-id>/`
- override with `QW1_EVIDENCE_ROOT=/abs/path`
- metadata: `meta.txt`
- per-step logs: `<script>.log`
- execution summary: `results.tsv`
