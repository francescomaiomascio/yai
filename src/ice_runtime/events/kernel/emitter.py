"""
ICE Runtime — Event Emitter
Unico punto di emissione eventi

Questo modulo è l'unico gateway:
- validazione
- autorità
- persistenza
"""

from __future__ import annotations

from .event import ICEEvent
from .validator import validate_event
from .authority import is_origin_authorized
from .store import EventStore


class EventEmissionError(Exception):
    """Evento illegale o non conforme."""
    pass


class EventEmitter:
    """
    L'Emitter è l'unico componente autorizzato a:
    - accettare eventi
    - validarli
    - persisterli

    Nessun altro modulo deve scrivere direttamente nello store.
    """

    def __init__(self, store: EventStore) -> None:
        self._store = store

    # =========================
    # API Principale
    # =========================

    def emit(self, event: ICEEvent) -> None:
        """
        Emissione ufficiale di un evento ICE.

        Ordine di enforcement (NON modificabile):
        1. Validazione strutturale + causale
        2. Controllo autorità
        3. Append-only persistence
        """

        # 1. Validazione schema + causalità
        validate_event(event)

        # 2. Controllo autorità
        if not is_origin_authorized(
            origin=event.origin,
            event_type=event.event_type,
        ):
            raise EventEmissionError(
                f"Origin '{event.origin}' not authorized to emit '{event.event_type}'"
            )

        # 3. Persistenza (atto irreversibile)
        self._store.append(event)

    # =========================
    # Accesso controllato
    # =========================

    @property
    def store(self) -> EventStore:
        """
        Espone lo store SOLO in lettura.

        Nessuna append esterna.
        """
        return self._store


"""
Clausola Finale:

- Tutti gli eventi passano da qui
- Se non passano → NON ESISTONO
- Non esistono eventi "interni", "di servizio" o "speciali"

Questo modulo rende ICE:
→ event-only
→ auditabile
→ replayable
→ deterministicamente verificabile
"""
