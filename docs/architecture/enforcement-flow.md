# Enforcement Flow

## Law-native handoff

Runtime command handling now performs a law resolution step before enforcement behavior is finalized.

Current handoff point:

- `lib/core/session/session.c`
- `yai_session_handle_control_call(...)`

## Flow

1. Build classification context from control payload.
2. Run domain discovery.
3. Build effective normative stack.
4. Resolve final effect + rationale.
5. Map effect to runtime response contract.
6. Return decision/evidence/trace payload fields.

## Effect mapping

- `deny` and `quarantine` map to policy-blocked status.
- `review_required` maps to explicit review-needed status.
- non-blocking effects remain `ok` with rationale attached.

This keeps enforcement decisions driven by resolved law output instead of ad-hoc local policy branches.
