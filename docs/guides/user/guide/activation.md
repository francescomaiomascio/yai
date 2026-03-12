# Activation

## Purpose
Describe activation and cognition entrypoints for user-facing understanding.

## Platform Surfaces
- Public API: `include/yai/knowledge/activation.h`
- Knowledge runtime: `include/yai/knowledge/runtime.h`
- Cognition implementation: `lib/knowledge/cognition/activation.c`
- Graph domain activation logic: `lib/graph/domains/activation.c`

## User-Level Contract
- Activation is deterministic for equal inputs and parameters.
- Activation outcomes are consumed through graph/knowledge read surfaces, not direct internal state mutation.
