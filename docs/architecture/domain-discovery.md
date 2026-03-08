# Domain Discovery

## Runtime role

`yai` maps runtime operations to family/domain/subdomain candidates before policy resolution.

## Inputs

- action class
- provider class
- protocol class
- resource class
- workspace and authority hints

## Discovery output

Discovery emits:
- `family_id`
- `domain_id` compatibility id (internal bridge output)
- specialization candidate set
- selected specialization
- family candidate ranking
- confidence and rationale

This output is consumed by resolver, which composes regulatory/sector/contextual overlays over the selected domain context.

## Runtime genericity pass I

Discovery now routes in this order:
1. classification signal extraction
2. family candidate scoring/ranking
3. specialization candidate selection within selected family
4. compatibility `domain_id` mapping for bridge continuity

Overlay-sensitive signals considered in runtime-facing paths:
- provider trust hints (for security-supply-chain)
- personal-data publication hints (for GDPR)
- high-risk experiment hints (for AI Act)
