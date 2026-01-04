"""
ICE Runtime — Error Definitions
===============================

Questo modulo definisce gli errori FONDATIVI del Runtime ICE.

Regole:
- Questi errori rappresentano violazioni strutturali
- NON sono recoverable dall'agente
- NON sono errori di dominio
- NON sono errori di IO
- Sono segnali di incoerenza del sistema o uso illegittimo

Se uno di questi errori emerge:
→ il Run DEVE abortire
→ il Runtime rimane sovrano
"""


class RuntimeError(Exception):
    """
    Errore base del Runtime ICE.

    Usato solo per:
    - uso illegittimo dell'API Runtime
    - violazioni di contratto interno
    - inconsistenze strutturali

    NON deve essere catturato da agenti o layer superiori.
    """
    pass


class RunNotFoundError(RuntimeError):
    """
    Sollevato quando un RunID non esiste nel Runtime.
    """
    pass


class RunAlreadyExecutedError(RuntimeError):
    """
    Sollevato quando si tenta di eseguire un Run già terminato.
    """
    pass


class InvalidRunStateError(RuntimeError):
    """
    Sollevato quando una transizione di stato non è ammessa
    dalla state machine RFC-ICE-005.
    """
    pass


class RuntimeInvariantViolation(RuntimeError):
    """
    Sollevato quando un invariante fondativo del Runtime
    viene violato.

    Questo è SEMPRE un bug.
    """
    pass
