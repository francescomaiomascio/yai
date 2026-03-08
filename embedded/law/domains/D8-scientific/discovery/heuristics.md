# D8-scientific discovery heuristics

Strong D8 signals:
- experiment run commands and pipeline control events
- explicit parameter-lock metadata (`params_hash`)
- scientific artifact binding (dataset/config/model references)

Confidence handling:
- high confidence when experiment command + parameter metadata + scientific assets are present
- medium confidence when one of provenance anchors is missing
- low confidence routes to `review_required`

Safety fallback:
- missing parameter lock or provenance minimum resolves to `deny`
- ambiguous dataset/config binding resolves to `quarantine`
