# Evidence Pipeline (In-Scope Segment)

## Scope for this tranche

Dataplane and persistence remain out of scope.
Runtime produces deterministic evidence shape and trace context.

## Compositional evidence model

Final evidence obligations are aggregated from:
- specialization base obligations
- regulatory overlay additive obligations
- sector overlay hardening obligations
- authority/escalation requirements
- retention/provenance requirements

## Overlay-driven hardening

Examples of additive fields from overlay composition:
- GDPR: lawful basis, subject category, cross-border flag
- AI Act: model context, oversight actor, high-risk review trace
- Finance: approval chain, amount context, counterparty context
- Security supply-chain: provider trust and dependency-chain references

## Produced artifacts

For each resolved call, runtime prepares:
- decision payload (family/domain/subdomain, effect, rationale)
- authority summary and escalation markers
- aggregated evidence envelope fields
- resolution trace JSON (classification, discovery, precedence, overlay/compliance attachments)

Evidence envelope now flags overlay-driven hardening explicitly:
- `approval_chain_required`
- `dependency_chain_required`
- `lawful_basis_required`
- `oversight_trace_required`

## Where generated

- decision/evidence mapping: `lib/law/mapping/decision_to_evidence.c`
- trace generation: `lib/law/debug/resolution_trace.c`
- runtime return wiring: `lib/core/session/session.c`
