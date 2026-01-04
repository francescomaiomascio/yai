"""
ICE Runtime — Memory Promotion
==============================

Questo modulo governa l'UNICO meccanismo con cui una memoria nasce.

Principio fondante:
- La memoria NON viene scritta
- La memoria NON viene mutata
- La memoria viene PROMOSSA da eventi validati

Questo modulo:
- verifica se un evento è promotabile
- costruisce l'oggetto memoria
- DELEGA al Runtime l'emissione dell'evento `MemoryPromoted`

NON:
- persiste direttamente
- espone memoria agli agenti
- prende decisioni semantiche arbitrarie
"""

from typing import Iterable, List
from datetime import datetime

from ice_runtime.events.kernel.event import Event
from ice_runtime.events.kernel.taxonomy import EventCategory
from ice_runtime.memory.errors import (
    MemoryPromotionError,
    NonPromotableEventError,
)
from ice_runtime.memory.registry import MemoryType
from ice_runtime.ids.runtime_id import MemoryID


class MemoryPromotionRequest:
    """
    Richiesta formale di promozione a memoria.

    È una STRUCT.
    Non fa nulla.
    """

    def __init__(
        self,
        *,
        source_events: List[Event],
        memory_type: MemoryType,
        confidence: float,
        created_at: datetime | None = None,
    ):
        self.source_events = source_events
        self.memory_type = memory_type
        self.confidence = confidence
        self.created_at = created_at or datetime.utcnow()


class MemoryPromotionService:
    """
    Servizio puro di promozione memoria.

    Non persiste.
    Non emette eventi.
    Non muta stato globale.

    Costruisce SOLO l'oggetto memoria.
    """

    @staticmethod
    def validate_events(events: Iterable[Event]) -> None:
        """
        Verifica che TUTTI gli eventi siano promotabili.
        """

        for event in events:
            if event.category != EventCategory.DOMAIN:
                raise NonPromotableEventError(
                    event_id=event.event_id,
                    reason="only DOMAIN events can be promoted to memory",
                )

            if not event.is_persistent:
                raise NonPromotableEventError(
                    event_id=event.event_id,
                    reason="event is not persistent",
                )

    @staticmethod
    def promote(request: MemoryPromotionRequest) -> dict:
        """
        Costruisce il payload della memoria.

        Ritorna una struttura pronta per:
        - evento `MemoryPromoted`
        - persistenza runtime-side
        """

        if not request.source_events:
            raise MemoryPromotionError("no source events provided")

        MemoryPromotionService.validate_events(request.source_events)

        memory_id = MemoryID.generate()

        return {
            "memory_id": memory_id,
            "memory_type": request.memory_type.value,
            "source_events": [e.event_id for e in request.source_events],
            "confidence": request.confidence,
            "created_at": request.created_at.isoformat(),
        }
