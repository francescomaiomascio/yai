# src/ice_runtime/events/kernel/event.py
"""
ICE Runtime — Event Kernel
Fondazione Assoluta

Questo modulo definisce COSA È un evento ICE.
Non contiene logica di emissione, validazione o persistenza.
Definisce esclusivamente la struttura, gli invarianti e il contratto.

Se questo file è errato, l'intero Runtime è errato.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Any, Dict, Optional, Tuple
from datetime import datetime
import hashlib
import json


# =========================
# Tipi primitivi espliciti
# =========================

EventID = str
RunID = str
EventType = str
Origin = str          # "runtime" | "agent:<id>" | "system"
Timestamp = datetime
Hash = str


# =========================
# Eccezioni Kernel
# =========================

class EventInvariantViolation(Exception):
    """Violazione di un invariante strutturale dell'evento."""
    pass


# =========================
# Evento ICE (Fondativo)
# =========================

@dataclass(frozen=True)
class ICEEvent:
    """
    Evento ICE immutabile.

    Un evento rappresenta un fatto accaduto durante un Run,
    osservabile e registrabile sotto controllo del Runtime.

    Un evento NON È:
    - una intenzione
    - una previsione
    - una promessa
    """

    # Identità
    event_id: EventID
    run_id: RunID
    event_type: EventType

    # Temporalità
    timestamp: Timestamp

    # Autorità
    origin: Origin  # runtime | agent:<id> | system

    # Contenuto
    payload: Dict[str, Any]

    # Causalità
    causality: Optional[Tuple[EventID, ...]] = None

    # Integrità
    integrity: Hash = field(init=False)

    # =========================
    # Post-init: invarianti
    # =========================

    def __post_init__(self):
        object.__setattr__(self, "integrity", self._compute_integrity())
        self._enforce_invariants()

    # =========================
    # Invarianti Hard
    # =========================

    def _enforce_invariants(self) -> None:
        if not self.event_id:
            raise EventInvariantViolation("event_id mancante")

        if not self.run_id:
            raise EventInvariantViolation("run_id mancante")

        if not self.event_type:
            raise EventInvariantViolation("event_type mancante")

        if not isinstance(self.timestamp, datetime):
            raise EventInvariantViolation("timestamp non valido")

        if not self.origin:
            raise EventInvariantViolation("origin mancante")

        if not isinstance(self.payload, dict):
            raise EventInvariantViolation("payload deve essere dict")

        if self.causality is not None:
            if not isinstance(self.causality, tuple):
                raise EventInvariantViolation("causality deve essere tuple")
            if len(self.causality) == 0:
                raise EventInvariantViolation("causality vuota non ammessa")

    # =========================
    # Integrità
    # =========================

    def _compute_integrity(self) -> Hash:
        """
        Calcola hash deterministico dell'evento.
        NON include il campo integrity stesso.
        """
        canonical = {
            "event_id": self.event_id,
            "run_id": self.run_id,
            "event_type": self.event_type,
            "timestamp": self.timestamp.isoformat(),
            "origin": self.origin,
            "payload": self.payload,
            "causality": self.causality,
        }

        encoded = json.dumps(
            canonical,
            sort_keys=True,
            separators=(",", ":"),
            default=str,
        ).encode("utf-8")

        return hashlib.sha256(encoded).hexdigest()

    # =========================
    # Serializzazione
    # =========================

    def to_dict(self) -> Dict[str, Any]:
        return {
            "event_id": self.event_id,
            "run_id": self.run_id,
            "event_type": self.event_type,
            "timestamp": self.timestamp.isoformat(),
            "origin": self.origin,
            "payload": self.payload,
            "causality": self.causality,
            "integrity": self.integrity,
        }

