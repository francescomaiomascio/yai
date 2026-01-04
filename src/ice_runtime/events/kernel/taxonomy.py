# src/ice_runtime/events/kernel/taxonomy.py
"""
ICE Runtime — Event Taxonomy
RFC-ICE-007 (v1)

Questo modulo definisce la TASSOMIA CHIUSA degli eventi ICE.

Se un event_type non è definito qui:
- NON ESISTE
- DEVE essere rigettato
- NON può essere emesso, validato o persistito

Questo file è normativa, non configurazione.
"""

from __future__ import annotations

from enum import Enum
from typing import FrozenSet


# =========================
# Categorie Canoniche
# =========================

class EventCategory(str, Enum):
    RUNTIME = "runtime"
    COGNITIVE = "cognitive"
    DOMAIN = "domain"
    MEMORY = "memory"
    CAPABILITY = "capability"


# =========================
# Runtime Events (Lifecycle)
# =========================

RUNTIME_EVENTS: FrozenSet[str] = frozenset({
    "RunProvisioned",
    "ResourcesAllocated",
    "ContextResolved",
    "MemoryMounted",
    "CapabilitiesBound",
    "ValidationStarted",
    "ValidationPassed",
    "ValidationFailed",
    "RunCommitted",
    "RunAborted",
    "AbortReasonDeclared",
    "ResourcesReleased",
    "RunTerminated",
})


# =========================
# Cognitive Events
# =========================

COGNITIVE_EVENTS: FrozenSet[str] = frozenset({
    "InferenceStep",
    "DecisionProposed",
    "HypothesisGenerated",
    "UncertaintyDeclared",
    "PlanStepProposed",
})


# =========================
# Domain Events
# =========================

DOMAIN_EVENTS: FrozenSet[str] = frozenset({
    "FileRead",
    "FileWritten",
    "TaskStarted",
    "TaskCompleted",
    "APIRequestExecuted",
    "UserNotificationSent",
    "WorkflowAdvanced",
})


# =========================
# Memory Events
# =========================

MEMORY_EVENTS: FrozenSet[str] = frozenset({
    "MemoryPromoted",
    "MemoryExpired",
    "MemoryDeprecated",
    "MemorySuperseded",
    "MemoryInvalidated",
})


# =========================
# Capability Events
# =========================

CAPABILITY_EVENTS: FrozenSet[str] = frozenset({
    "CapabilityRequested",
    "CapabilityGranted",
    "CapabilityUsed",
    "CapabilityRevoked",
    "CapabilityExpired",
})


# =========================
# Indici Derivati
# =========================

ALL_EVENTS: FrozenSet[str] = frozenset().union(
    RUNTIME_EVENTS,
    COGNITIVE_EVENTS,
    DOMAIN_EVENTS,
    MEMORY_EVENTS,
    CAPABILITY_EVENTS,
)


EVENT_CATEGORY_MAP = {
    **{e: EventCategory.RUNTIME for e in RUNTIME_EVENTS},
    **{e: EventCategory.COGNITIVE for e in COGNITIVE_EVENTS},
    **{e: EventCategory.DOMAIN for e in DOMAIN_EVENTS},
    **{e: EventCategory.MEMORY for e in MEMORY_EVENTS},
    **{e: EventCategory.CAPABILITY for e in CAPABILITY_EVENTS},
}


# =========================
# API di Verifica (Kernel)
# =========================

def is_valid_event_type(event_type: str) -> bool:
    """
    Verifica se un event_type è ammesso dal Runtime.
    """
    return event_type in ALL_EVENTS


def category_of(event_type: str) -> EventCategory:
    """
    Ritorna la categoria canonica di un event_type.

    Solleva KeyError se l'evento non è ammesso.
    """
    return EVENT_CATEGORY_MAP[event_type]


# =========================
# Clausola di Chiusura
# =========================

"""
Questo modulo NON deve:
- essere esteso dinamicamente
- leggere configurazioni
- accettare override

La tassonomia è chiusa per definizione.

Aggiungere un evento richiede:
- nuova RFC
- nuova versione
- modifica esplicita di questo file
"""
