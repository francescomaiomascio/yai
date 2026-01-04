"""
ICE Runtime — Event Validator
RFC-ICE-003 · Event Model
RFC-ICE-007 · Event Taxonomy

Questo modulo decide se un evento ICE è:
- strutturalmente valido
- causalmente valido
- temporalmente valido

Se un evento fallisce qui:
NON ESISTE.
"""

from __future__ import annotations

from typing import Iterable, Mapping, Set
from uuid import UUID
from datetime import datetime

from .event import ICEEvent
from .taxonomy import EVENT_TAXONOMY
from .authority import is_origin_authorized


# =========================
# Errori Canonici
# =========================

class EventValidationError(Exception):
    """Errore base di validazione evento."""


class StructuralViolation(EventValidationError):
    pass


class AuthorityViolation(EventValidationError):
    pass


class CausalityViolation(EventValidationError):
    pass


class TemporalViolation(EventValidationError):
    pass


# =========================
# Validator Principale
# =========================

class EventValidator:
    """
    Validator stateless.

    Ogni metodo solleva eccezione se l'evento NON È valido.
    """

    # ---------------------
    # Entry point
    # ---------------------

    @staticmethod
    def validate(
        event: ICEEvent,
        *,
        known_event_ids: Set[UUID],
        last_timestamp: datetime | None = None,
    ) -> None:
        """
        Valida un evento ICE.

        Args:
            event: evento da validare
            known_event_ids: eventi già presenti nel Run
            last_timestamp: ultimo timestamp noto del Run

        Raises:
            EventValidationError
        """
        EventValidator._validate_structure(event)
        EventValidator._validate_taxonomy(event)
        EventValidator._validate_authority(event)
        EventValidator._validate_temporal(event, last_timestamp)
        EventValidator._validate_causality(event, known_event_ids)

    # ---------------------
    # Validazioni
    # ---------------------

    @staticmethod
    def _validate_structure(event: ICEEvent) -> None:
        if not isinstance(event.event_id, UUID):
            raise StructuralViolation("event_id must be UUID")

        if not isinstance(event.run_id, UUID):
            raise StructuralViolation("run_id must be UUID")

        if not isinstance(event.timestamp, datetime):
            raise StructuralViolation("timestamp must be datetime")

    @staticmethod
    def _validate_taxonomy(event: ICEEvent) -> None:
        if event.event_type not in EVENT_TAXONOMY:
            raise StructuralViolation(
                f"Unknown event_type '{event.event_type}'"
            )

    @staticmethod
    def _validate_authority(event: ICEEvent) -> None:
        if not is_origin_authorized(
            origin=event.origin,
            event_type=event.event_type,
        ):
            raise AuthorityViolation(
                f"Origin '{event.origin}' not authorized for "
                f"event_type '{event.event_type}'"
            )

    @staticmethod
    def _validate_temporal(
        event: ICEEvent,
        last_timestamp: datetime | None,
    ) -> None:
        if last_timestamp is None:
            return

        if event.timestamp < last_timestamp:
            raise TemporalViolation(
                "Event timestamp goes backwards in time"
            )

    @staticmethod
    def _validate_causality(
        event: ICEEvent,
        known_event_ids: Set[UUID],
    ) -> None:
        causality = event.causality or {}

        parent_id = causality.get("parent_event_id")
        if parent_id is not None:
            try:
                parent_uuid = UUID(parent_id)
            except Exception:
                raise CausalityViolation(
                    "parent_event_id is not a valid UUID"
                )

            if parent_uuid not in known_event_ids:
                raise CausalityViolation(
                    "parent_event_id references unknown event"
                )

        correlation_id = causality.get("correlation_id")
        if correlation_id is not None:
            try:
                UUID(correlation_id)
            except Exception:
                raise CausalityViolation(
                    "correlation_id is not a valid UUID"
                )


# =========================
# Clausola Finale
# =========================

"""
Questo modulo NON decide se un evento è utile.
Decide solo se può esistere.

Ogni evento che passa questo validator:
- è coerente
- è tracciabile
- è auditabile
- è replayable

Ogni evento che non lo passa:
NON ENTRA NEL SISTEMA.
"""
