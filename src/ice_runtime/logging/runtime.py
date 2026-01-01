from __future__ import annotations

import os
from datetime import datetime
from pathlib import Path


class RuntimeContext:
    def __init__(
        self,
        runtime_id: str,
        base_dir: Path,
    ):
        self.runtime_id = runtime_id
        self.started_at = datetime.utcnow()
        self.base_dir = base_dir
        self.phase = "preboot"

    def set_phase(self, phase: str) -> None:
        self.phase = phase


def _require_launch_dir() -> Path:
    raw = os.environ.get("ICE_LAUNCH_DIR")
    if not raw:
        raise RuntimeError("ICE_LAUNCH_DIR not set")
    return Path(raw)


def init_preboot_context() -> RuntimeContext:
    launch = _require_launch_dir()
    preboot_dir = launch / "preboot"
    preboot_dir.mkdir(parents=True, exist_ok=True)
    return RuntimeContext(
        runtime_id="preboot",
        base_dir=preboot_dir,
    )


def init_runtime_context() -> RuntimeContext:
    launch = _require_launch_dir()
    phase = os.environ.get("ICE_PHASE")
    if phase != "runtime":
        raise RuntimeError("Runtime logging requested outside runtime phase")
    runtime_dir = launch / "runtime"
    if not runtime_dir.exists():
        raise RuntimeError("Runtime not initialized yet")
    return RuntimeContext(
        runtime_id="runtime",
        base_dir=runtime_dir,
    )


LoggingRuntime = RuntimeContext
