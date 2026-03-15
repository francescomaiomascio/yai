# obs

Cross-cutting observability surface for YAI.

## Scope

This root namespace owns shared observability runtime material and service
entrypoints that are not specific to a single subsystem.

## Contents

- `cmd/auditd/`: audit-oriented service entrypoint
- `cmd/metricsd/`: metrics-oriented service entrypoint
- `metrics/`: metrics collection/export helpers
- `reporting/`: reporting snapshots and summaries
- `traces/`: trace snapshot/export helpers

## Boundary

Subsystems such as cognition, state, orchestration, governance, and runtime may
produce observability data, but the shared observability surface lives here.
