from __future__ import annotations

"""
ICE Runtime Bootstrap
=====================

Bootstrap minimale del Runtime ICE.

Responsabilità:
- costruire EventKernel
- costruire EventEmitter
- inizializzare logging runtime-side
- istanziare Runtime in stato coerente

NON:
- orchestrazione
- engine
- AI
- storage di dominio
"""

from pathlib import Path
from typing import Optional

from ice_runtime.runtime.runtime import Runtime
from ice_runtime.events.kernel.emitter import EventEmitter
from ice_runtime.events.kernel.store import EventStore

from ice_runtime.logging.router import LogRouter
from ice_runtime.logging.runtime import RuntimeContext
from ice_runtime.logging.api import init as init_logging
from ice_runtime.logging.sinks.stdout import StdoutSink


# ============================================================================
# PUBLIC API
# ============================================================================

def bootstrap_runtime(
    *,
    base_dir: Optional[Path] = None,
    runtime_id: str = "ice-runtime",
    enable_stdout_logs: bool = True,
) -> Runtime:
    """
    Costruisce e restituisce un Runtime ICE pronto all'uso.

    Effetti consentiti:
    - inizializzazione logging runtime-side
    - costruzione kernel eventi

    Nessun engine.
    Nessuna orchestrazione.
    """

    # ------------------------------------------------------------------
    # Runtime identity
    # ------------------------------------------------------------------

    base_dir = (base_dir or Path.cwd()).resolve()

    runtime_ctx = RuntimeContext(
        runtime_id=runtime_id,
        base_dir=base_dir,
    )

    # ------------------------------------------------------------------
    # Logging (runtime-owned)
    # ------------------------------------------------------------------

    sinks = [StdoutSink()] if enable_stdout_logs else []
    log_router = LogRouter(runtime_ctx, sinks=sinks)
    init_logging(log_router)

    # ------------------------------------------------------------------
    # Event Kernel (realtà primaria)
    # ------------------------------------------------------------------

    event_store = EventStore()
    event_emitter = EventEmitter(store=event_store)

    # ------------------------------------------------------------------
    # Runtime (stato iniziale controllato)
    # ------------------------------------------------------------------

    runtime = Runtime(
        runtime_id=runtime_id,
        base_dir=base_dir,
        emitter=event_emitter,
        event_store=event_store,
        log_router=log_router,
    )

    runtime.mark_bootstrapped()

    return runtime
