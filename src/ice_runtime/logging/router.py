from pathlib import Path
import re
import traceback

from .event import LogEvent
from .runtime import RuntimeContext

_SAFE_SEGMENT = re.compile(r"[^a-zA-Z0-9._-]+")


def _safe_segment(value: str | None, fallback: str) -> str:
    if not value:
        return fallback
    cleaned = _SAFE_SEGMENT.sub("_", value.strip())
    return cleaned or fallback


def resolve_log_path(event: LogEvent, ctx: RuntimeContext) -> Path:
    phase = _safe_segment(ctx.phase, "preboot")
    domain = _safe_segment(event.domain, "runtime")
    owner = _safe_segment(event.owner, "general")
    owner_lower = owner.lower()

    if domain == "preboot":
        return Path("preboot.log")
    if domain == "icenet":
        return Path("icenet") / f"{owner}.log"
    if domain == "ui":
        phase_override = None
        if isinstance(event.data, dict):
            phase_override = event.data.get("phase")
        ui_phase = _safe_segment(phase_override or phase, "preboot")
        return Path("ui") / ui_phase / "renderer.log"
    if domain == "backend":
        if owner_lower in {"ws", "icews"}:
            return Path("backend") / "ws" / "ws.log"
        if owner_lower == "core":
            return Path("backend") / "core" / "backend-core.log"
        if owner_lower == "dashboard":
            return Path("backend") / "dashboard" / "backend-dashboard.log"
        if owner_lower == "ipc":
            return Path("backend") / "dashboard" / "ipc.log"
        if phase == "preboot":
            return Path("backend") / "preboot" / "backend-preboot.log"
        return Path("backend") / phase / f"backend-{owner}.log"
    if domain == "llm":
        return Path("llm") / phase / "llm.log"
    if domain == "audit":
        return Path("audit") / f"{owner}.log"
    return Path("runtime.log")


class LogRouter:
    def __init__(self, runtime: RuntimeContext, transports):
        self.runtime = runtime
        self.transports = transports

    def route(self, event: LogEvent):
        phase = (self.runtime.phase or "preboot").lower()
        domain = (event.domain or "").lower()
        scope = (event.scope or "").lower()

        if phase == "preboot":
            if domain not in {"preboot", "ui", "icenet", "backend"}:
                return
            if domain == "backend" and "preboot" not in scope:
                return
        elif phase == "runtime":
            if domain == "preboot":
                return

        for transport in self.transports:
            transport.send(event)


class StructuredLogger:
    def __init__(self, domain: str, owner: str, scope: str):
        self.domain = domain
        self.owner = owner
        self.scope = scope

    def _emit(
        self,
        level: str,
        msg: str,
        *args: object,
        data: object | None = None,
        extra: dict | None = None,
        exc_info: bool | BaseException | None = None,
    ) -> None:
        from .api import emit

        if args:
            text = str(msg) % args
        else:
            text = str(msg)
        payload: dict | None = None
        if isinstance(extra, dict):
            payload = dict(extra)
        if data is not None:
            if payload is None:
                payload = {}
            if isinstance(data, dict):
                payload.update(data)
            else:
                payload["data"] = data
        if exc_info:
            if payload is None:
                payload = {}
            payload["exception"] = traceback.format_exc()
        emit(
            LogEvent(
                LogEvent.now(),
                level,
                self.domain,
                self.owner,
                self.scope,
                text,
                payload,
                None,
            )
        )

    def info(self, msg: str, *args: object, **kwargs: object) -> None:
        self._emit("INFO", msg, *args, **kwargs)

    def debug(self, msg: str, *args: object, **kwargs: object) -> None:
        self._emit("DEBUG", msg, *args, **kwargs)

    def warn(self, msg: str, *args: object, **kwargs: object) -> None:
        self._emit("WARN", msg, *args, **kwargs)

    def error(self, msg: str, *args: object, **kwargs: object) -> None:
        self._emit("ERROR", msg, *args, **kwargs)

    def warning(self, msg: str, *args: object, **kwargs: object) -> None:
        self._emit("WARN", msg, *args, **kwargs)

    def exception(self, msg: str, *args: object, **kwargs: object) -> None:
        kwargs.setdefault("exc_info", True)
        self._emit("ERROR", msg, *args, **kwargs)

    def critical(self, msg: str, *args: object, **kwargs: object) -> None:
        self._emit("FATAL", msg, *args, **kwargs)

    def setLevel(self, _level: object) -> None:
        return None


def get_logger(domain: str, owner: str, scope: str) -> StructuredLogger:
    return StructuredLogger(domain, owner, scope)
