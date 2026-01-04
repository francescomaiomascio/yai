"""
ICE Runtime — Memory Errors
==========================

Errori formali del sottosistema Memory.

Regola:
- Ogni errore è deterministico
- Ogni errore è spiegabile
- Nessun errore è silenzioso
"""


class MemoryError(Exception):
    """
    Errore base del sottosistema Memory.

    NON va mai lanciato direttamente.
    Serve solo per catch strutturato.
    """
    pass


class MemoryPromotionError(MemoryError):
    """
    Errore durante la promozione di una memoria.
    """
    def __init__(self, message: str):
        super().__init__(message)


class NonPromotableEventError(MemoryPromotionError):
    """
    Evento non ammissibile alla promozione a memoria.
    """

    def __init__(self, *, event_id: str, reason: str):
        self.event_id = event_id
        self.reason = reason
        super().__init__(
            f"event '{event_id}' cannot be promoted to memory: {reason}"
        )


class MemoryRegistryError(MemoryError):
    """
    Errori di registrazione / lookup memoria.
    """
    pass


class MemoryNotFoundError(MemoryRegistryError):
    """
    Memoria richiesta inesistente.
    """

    def __init__(self, memory_id: str):
        self.memory_id = memory_id
        super().__init__(f"memory '{memory_id}' not found")


class MemoryLifecycleError(MemoryError):
    """
    Violazione del lifecycle della memoria.
    """
    pass


class MemoryExpiredError(MemoryLifecycleError):
    """
    Accesso a memoria scaduta.
    """

    def __init__(self, memory_id: str):
        self.memory_id = memory_id
        super().__init__(f"memory '{memory_id}' is expired")


class MemoryAccessViolation(MemoryError):
    """
    Violazione delle policy di accesso alla memoria.
    """

    def __init__(self, *, memory_id: str, actor: str):
        self.memory_id = memory_id
        self.actor = actor
        super().__init__(
            f"actor '{actor}' is not allowed to access memory '{memory_id}'"
        )
