# Resolution Debugging

## Debug surfaces

`lib/law/debug/` provides lightweight runtime-inspection helpers:

- `dump_discovery_result.c`
- `dump_effective_stack.c`
- `resolution_trace.c`

## What to inspect first

1. Classification context values.
2. Discovery winner + confidence.
3. Applied/skipped rules in trace output.
4. Final effect mapping and rationale.

## Quick validation

Use the law-native suites:

```bash
make test-law
```

This executes unit coverage for loader/discovery/resolution and integration smoke for D1/D8/cross-domain behavior.
