"""
ICE Runtime — Event Store
Append-only event log

Questo modulo è l'unica sorgente di persistenza degli eventi.
Non interpreta. Non valida. Non filtra.
Registra.
"""

from __future__ import annotations

from typing import Iterable, List
from threading import Lock

from .event import ICEEvent


class EventStore:
    """
    Append-only, in-memory event store.

    - Nessuna mutazione
    - Nessuna cancellazione
    - Nessun update
    """

    def __init__(self) -> None:
        self._events: List[ICEEvent] = []
        self._lock = Lock()

    # =========================
    # Scrittura
    # =========================

    def append(self, event: ICEEvent) -> None:
        """
        Appende un evento al log.

        L'evento si assume già VALIDATO.
        """
        with self._lock:
            self._events.append(event)

    # =========================
    # Lettura
    # =========================

    def all(self) -> List[ICEEvent]:
        """
        Restituisce tutti gli eventi in ordine causale.
        """
        with self._lock:
            return list(self._events)

    def by_run(self, run_id: str) -> List[ICEEvent]:
        """
        Restituisce gli eventi appartenenti a un Run.
        """
        with self._lock:
            return [e for e in self._events if e.run_id == run_id]

    def last(self) -> ICEEvent | None:
        """
        Ultimo evento emesso.
        """
        with self._lock:
            return self._events[-1] if self._events else None

    # =========================
    # Introspezione
    # =========================

    def __len__(self) -> int:
        return len(self._events)

    def __iter__(self) -> Iterable[ICEEvent]:
        return iter(self.all())


"""
Clausola Fondativa:

- Se un evento non è nel store → NON è mai accaduto
- Il Runtime NON ha memoria fuori da questo log
- Ogni replay parte ESCLUSIVAMENTE da qui
"""
