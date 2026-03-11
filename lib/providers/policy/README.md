# Provider Policy

`lib/providers/policy/` contains provider admissibility policy used by selection.

Responsibilities:

- trust-level thresholds per capability class
- mock-provider allowance/denial
- policy checks for registry descriptors

Protocol contracts remain under `protocol/`; this layer applies runtime policy.
