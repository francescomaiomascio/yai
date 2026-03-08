# Evidence Pipeline (In-Scope Segment)

## Scope for this tranche

Dataplane and persistence are intentionally out of scope.

In this tranche, runtime produces evidence *shape* and trace context only.

## Produced artifacts

For each resolved control call, runtime prepares:

- decision payload (domain, effect, rationale)
- evidence envelope fields (requirements, trace id, domain)
- resolution trace JSON (classification, discovery, precedence)

## Where generated

- decision/evidence mapping: `lib/law/mapping/decision_to_evidence.c`
- trace generation: `lib/law/debug/resolution_trace.c`
- runtime return payload wiring: `lib/core/session/session.c`

## Next boundary

Persistence/query/export remain deferred to dataplane tranche.
