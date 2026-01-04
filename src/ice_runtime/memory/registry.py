"""
ICE Runtime — Memory Registry
=============================

Registry sovrano delle memorie persistenti.

Principi:
- La memoria NON è stato
- La memoria è derivata da eventi validati
- La memoria è immutabile
- La sostituzione avviene solo per superseding
"""

from typing import Dict, Iterable, Optional

from .errors import (
    MemoryNotFoundError,
    MemoryRegistryError,
)


class MemoryRecord:
    """
    Rappresentazione immutabile di una memoria registrata.
    """

    __slots__ = (
        "memory_id",
        "memory_type",
        "payload",
        "confidence",
        "lifecycle_policy",
        "access_policy",
        "source_events",
        "schema_version",
    )

    def __init__(
        self,
        *,
        memory_id: str,
        memory_type: str,
        payload: dict,
        confidence: float,
        lifecycle_policy: dict,
        access_policy: dict,
        source_events: Iterable[str],
        schema_version: str,
    ):
        self.memory_id = memory_id
        self.memory_type = memory_type
        self.payload = payload
        self.confidence = confidence
        self.lifecycle_policy = lifecycle_policy
        self.access_policy = access_policy
        self.source_events = tuple(source_events)
        self.schema_version = schema_version


class MemoryRegistry:
    """
    Registry centrale delle memorie ICE.

    - NON gestisce lifecycle
    - NON valida policy
    - NON espone viste

    Tiene solo verità strutturali.
    """

    def __init__(self) -> None:
        self._memories: Dict[str, MemoryRecord] = {}

    # -------------------------------------------------
    # Registration
    # -------------------------------------------------

    def register(self, record: MemoryRecord) -> None:
        """
        Registra una nuova memoria.

        Vietato:
        - sovrascrivere una memoria esistente
        """
        if record.memory_id in self._memories:
            raise MemoryRegistryError(
                f"memory '{record.memory_id}' already registered"
            )

        self._memories[record.memory_id] = record

    # -------------------------------------------------
    # Lookup
    # -------------------------------------------------

    def get(self, memory_id: str) -> MemoryRecord:
        """
        Recupera una memoria per ID.
        """
        try:
            return self._memories[memory_id]
        except KeyError:
            raise MemoryNotFoundError(memory_id)

    def exists(self, memory_id: str) -> bool:
        """
        Verifica esistenza memoria.
        """
        return memory_id in self._memories

    # -------------------------------------------------
    # Iteration
    # -------------------------------------------------

    def all(self) -> Iterable[MemoryRecord]:
        """
        Itera tutte le memorie registrate.
        """
        return self._memories.values()

    # -------------------------------------------------
    # Introspection
    # -------------------------------------------------

    def count(self) -> int:
        """
        Numero di memorie registrate.
        """
        return len(self._memories)

    def snapshot(self) -> Dict[str, MemoryRecord]:
        """
        Snapshot read-only del registry.
        """
        return dict(self._memories)
