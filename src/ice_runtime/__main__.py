# src/ice_runtime/__main__.py
from __future__ import annotations

import sys
import time
import signal
from pathlib import Path
from typing import Optional
import os
from ice_runtime.bootstrap.bootstrap import bootstrap_runtime
from ice_runtime.logging.api import init_logging, get_logger


logger = get_logger("ice.runtime.main")

_runtime = None
_shutdown_requested = False


def _resolve_runtime_root() -> Path:
    """
    Risolve la root del Runtime.

    Oggi: cwd
    Domani: flag CLI / env / config
    """
    return Path.cwd().resolve()


def _shutdown(reason: str, signum: Optional[int] = None) -> None:
    """
    Shutdown idempotente del Runtime.
    """
    global _shutdown_requested, _runtime

    if _shutdown_requested:
        return

    _shutdown_requested = True

    logger.info(
        "runtime.shutdown.requested",
        reason=reason,
        signal=signum,
    )

    if _runtime is not None:
        try:
            _runtime.stop()
            logger.info("runtime.stopped")
        except Exception:
            logger.exception("runtime.stop.failed")

    sys.exit(0)


def _handle_signal(signum: int, frame=None) -> None:
    _shutdown(reason="signal", signum=signum)


def main() -> None:
    global _runtime

    # Logging minimale: il resto lo governa il bootstrap
    init_logging()

    logger.info("runtime.process.starting", pid=os.getpid())

    # Signal handling (POSIX-safe)
    signal.signal(signal.SIGINT, _handle_signal)
    signal.signal(signal.SIGTERM, _handle_signal)

    runtime_root = _resolve_runtime_root()

    try:
        _runtime = bootstrap_runtime(runtime_root)

        logger.info(
            "runtime.started",
            status=_runtime.status(),
            root=str(runtime_root),
        )

        # Processo long-lived
        while True:
            time.sleep(3600)

    except Exception:
        logger.exception("runtime.crashed")
        _shutdown(reason="crash")


if __name__ == "__main__":
    main()
