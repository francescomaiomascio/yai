"""
ICE Runtime — Event Authority
RFC-ICE-007 · Event Taxonomy v1

Questo modulo definisce l'AUTORITÀ di emissione degli eventi.
Non decide SE un evento è valido semanticamente.
Decide CHI può emetterlo.

Violazione = evento illegale.
"""

from __future__ import annotations

from typing import Dict, Set

from .taxonomy import EVENT_TAXONOMY


# =========================
# Tipi di Origin Canonici
# =========================

RUNTIME_ORIGIN = "runtime"
SYSTEM_ORIGIN = "system"
AGENT_PREFIX = "agent:"


# =========================
# Costruzione Mappa Autorità
# =========================

# Mappa: event_type -> origin autorizzati
_EVENT_AUTHORITY: Dict[str, Set[str]] = {}


def _build_authority_table() -> None:
    """
    Costruisce la tabella di autorità a partire
    dalla Event Taxonomy canonica.

    Chiamata UNA SOLA VOLTA a import-time.
    """
    for event_type, meta in EVENT_TAXONOMY.items():
        category = meta["category"]

        if category == "RUNTIME":
            _EVENT_AUTHORITY[event_type] = {RUNTIME_ORIGIN}

        elif category == "COGNITIVE":
            _EVENT_AUTHORITY[event_type] = {AGENT_PREFIX}

        elif category == "DOMAIN":
            _EVENT_AUTHORITY[event_type] = {RUNTIME_ORIGIN}

        elif category == "MEMORY":
            _EVENT_AUTHORITY[event_type] = {RUNTIME_ORIGIN}

        elif category == "CAPABILITY":
            # richiesta dall'agente, resto runtime
            if event_type == "CapabilityRequested":
                _EVENT_AUTHORITY[event_type] = {AGENT_PREFIX}
            else:
                _EVENT_AUTHORITY[event_type] = {RUNTIME_ORIGIN}

        else:
            # Tassonomia non valida → errore di sviluppo
            raise RuntimeError(
                f"Unknown event category '{category}' for {event_type}"
            )


_build_authority_table()


# =========================
# API Pubblica
# =========================

def is_origin_authorized(*, origin: str, event_type: str) -> bool:
    """
    Verifica se un origin è autorizzato a emettere un event_type.

    Args:
        origin: stringa origin (runtime | system | agent:<id>)
        event_type: tipo evento canonico

    Returns:
        True se autorizzato, False altrimenti
    """
    allowed = _EVENT_AUTHORITY.get(event_type)
    if allowed is None:
        return False

    if origin in allowed:
        return True

    # gestione agenti dinamici
    if any(a == AGENT_PREFIX for a in allowed):
        return origin.startswith(AGENT_PREFIX)

    return False


def allowed_origins_for(event_type: str) -> Set[str]:
    """
    Restituisce l'insieme degli origin autorizzati
    per un dato event_type.

    Usato per introspezione, debug, audit.
    """
    return set(_EVENT_AUTHORITY.get(event_type, set()))


# =========================
# Clausola Finale
# =========================

"""
Questo modulo è una legge, non una policy.

- Gli Agenti NON POSSONO mai emettere eventi di Runtime
- Il Runtime è l'unica autorità causale
- Nessun evento "ibrido" è ammesso
- Nessuna escalation implicita è possibile

Se un evento passa questo controllo:
→ chi lo emette è legittimato

Se non lo passa:
→ l'evento NON DEVE essere accettato
"""
