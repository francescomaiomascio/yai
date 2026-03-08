# Domain Discovery

## Runtime role

`yai` uses embedded law discovery profiles to map a runtime operation to a normative domain before resolution.

## Inputs

Discovery consumes the normalized classification context:

- action class (`egress`, `publish`, `retrieve`, `transform`, `infer`, `actuate`)
- provider class (for example `github`, `otel`, `s3`)
- protocol class (for example `http`, `grpc`, `file`)
- resource class (for example `dataset`, `artifact`, `credential`)
- workspace hints (mode, black-box flag, parameter-lock hints)

## Matching pipeline

1. Build signal set from classification.
2. Match signals against domain discovery profiles.
3. Compute deterministic confidence score.
4. Select best candidate domain.
5. If ambiguous, trigger fallback resolution path.

Current primary coverage is D1 (digital) and D8 (scientific).

## Output

Discovery emits:

- resolved domain id
- confidence score
- match rationale
- ambiguity/fallback marker

This output is then consumed by the law resolver stack builder.
