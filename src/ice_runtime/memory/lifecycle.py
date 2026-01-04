"""
ICE Runtime — Memory Lifecycle

Governance del ciclo di vita delle memorie persistenti.
Questo modulo NON espone accesso diretto agli agenti.

Responsabilità:
- expiry
- deprecazione
- sostituzione
- invalidazione

Ogni transizione produce eventi MEMORY canonici.
"""

from __future__ import annotations

from dataclasses import dataclass
from enum import Enum
from typing import Optional, Dict

from ice_runtime.events.kernel.emitter import emit_event
from ice_runtime.events.kernel.taxonomy import EventType
from ice_runtime.memory.errors import MemoryLifecycleError


class MemoryStatus(str, Enum):
    ACTIVE = "active"
    EXPIRED = "expired"
    DEPRECATED = "deprecated"
    SUPERSEDED = "superseded"
    INVALIDATED = "invalidated"


@dataclass(frozen=True)
class MemoryLifecycleState:
    memory_id: str
    status: MemoryStatus
    replaced_by: Optional[str] = None
    reason: Optional[str] = None


class MemoryLifecycleManager:
    """
    Autorità unica sul lifecycle delle memorie.

    Nessuna mutazione silenziosa.
    Nessuna transizione implicita.
    """

    def __init__(self) -> None:
        self._states: Dict[str, MemoryLifecycleState] = {}

    # =====================================================
    # QUERY
    # =====================================================

    def get_state(self, memory_id: str) -> MemoryLifecycleState:
        try:
            return self._states[memory_id]
        except KeyError:
            raise MemoryLifecycleError(
                f"Lifecycle state not found for memory {memory_id}"
            )

    def is_active(self, memory_id: str) -> bool:
        return self.get_state(memory_id).status == MemoryStatus.ACTIVE

    # =====================================================
    # TRANSITIONS
    # =====================================================

    def register_new(self, memory_id: str) -> None:
        if memory_id in self._states:
            raise MemoryLifecycleError(
                f"Memory {memory_id} already registered in lifecycle"
            )

        self._states[memory_id] = MemoryLifecycleState(
            memory_id=memory_id,
            status=MemoryStatus.ACTIVE,
        )

    def expire(self, memory_id: str, reason: str) -> None:
        self._transition(
            memory_id=memory_id,
            new_status=MemoryStatus.EXPIRED,
            event_type=EventType.MEMORY_EXPIRED,
            reason=reason,
        )

    def deprecate(self, memory_id: str, reason: str) -> None:
        self._transition(
            memory_id=memory_id,
            new_status=MemoryStatus.DEPRECATED,
            event_type=EventType.MEMORY_DEPRECATED,
            reason=reason,
        )

    def supersede(
        self,
        memory_id: str,
        new_memory_id: str,
        reason: str,
    ) -> None:
        self._transition(
            memory_id=memory_id,
            new_status=MemoryStatus.SUPERSEDED,
            event_type=EventType.MEMORY_SUPERSEDED,
            replaced_by=new_memory_id,
            reason=reason,
        )

    def invalidate(self, memory_id: str, reason: str) -> None:
        self._transition(
            memory_id=memory_id,
            new_status=MemoryStatus.INVALIDATED,
            event_type=EventType.MEMORY_INVALIDATED,
            reason=reason,
        )

    # =====================================================
    # INTERNAL
    # =====================================================

    def _transition(
        self,
        *,
        memory_id: str,
        new_status: MemoryStatus,
        event_type: EventType,
        reason: str,
        replaced_by: Optional[str] = None,
    ) -> None:
        state = self.get_state(memory_id)

        if state.status != MemoryStatus.ACTIVE:
            raise MemoryLifecycleError(
                f"Illegal lifecycle transition: {memory_id} is {state.status}"
            )

        new_state = MemoryLifecycleState(
            memory_id=memory_id,
            status=new_status,
            replaced_by=replaced_by,
            reason=reason,
        )

        self._states[memory_id] = new_state

        emit_event(
            event_type=event_type,
            payload={
                "memory_id": memory_id,
                "new_status": new_status.value,
                "replaced_by": replaced_by,
                "reason": reason,
            },
        )
