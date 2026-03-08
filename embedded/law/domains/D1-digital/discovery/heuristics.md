# D1-digital discovery heuristics

Strong D1 signals:
- command/provider patterns for `curl`, OTEL exporter egress, S3 upload, GitHub issue comment publication
- external endpoint/resource classes mapped to `egress` or `publish`

Confidence handling:
- high confidence when provider + command + external resource align
- medium confidence when only partial telemetry exists
- low confidence falls back to `review_required`

Ambiguity handling:
- missing or conflicting authority context escalates to `quarantine`
- absent contract reference on external egress resolves to `deny`
