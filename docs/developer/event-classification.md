# Event Classification

## Purpose

Classification normalizes runtime inputs before discovery.

## Components

- `event_classifier.c`: builds base context from request payload
- `action_classifier.c`: maps operation to canonical action classes
- `provider_classifier.c`: extracts provider hints
- `resource_classifier.c`: extracts resource class hints
- `protocol_classifier.c`: derives protocol class
- `workspace_context.c`: derives workspace-mode hints

## Output contract

Classifier emits a single context object used by discovery and resolver modules.

Keep classifier deterministic and side-effect free.
