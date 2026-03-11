# Provider Selection

`lib/providers/selection/` resolves capability requests to admissible providers.

Responsibilities:

- capability-to-provider routing
- named-provider resolution
- fallback selection from registry metadata
- policy-aware admissibility checks

This layer is runtime-side infrastructure and does not own orchestration flow.
