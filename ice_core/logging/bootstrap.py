from __future__ import annotations

from .api import init as init_logging
from .router import LogRouter
from .runtime import init_preboot_context, init_runtime_context, RuntimeContext
from .transports.filesystem import FileSystemTransport


def init_logging_pipeline(phase: str) -> RuntimeContext:
    if phase == "preboot":
        ctx = init_preboot_context()
    elif phase == "runtime":
        ctx = init_runtime_context()
    else:
        raise ValueError(f"Unknown phase: {phase}")

    ctx.set_phase(phase)
    router = LogRouter(ctx, transports=[FileSystemTransport(ctx)])
    init_logging(router)
    return ctx
