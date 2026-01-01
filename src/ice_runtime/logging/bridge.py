from __future__ import annotations

import traceback
from typing import Any, Dict, Optional

from .api import emit
from .event import LogEvent


def _format_message(msg: Any, args: tuple[Any, ...]) -> str:
    if not args:
        return str(msg)
    try:
        return str(msg) % args
    except Exception:
        return f"{msg} {args}"


def _infer_domain(name: str) -> str:
    lower = name.lower()
    if lower.startswith("ice.preboot") or lower.startswith("ice_studio.preboot"):
        return "preboot"
    if lower.startswith("ice.network") or "icenet" in lower:
        return "icenet"
    if lower.startswith("ice.system"):
        return "runtime"
    if lower.startswith("ice_studio.backend") or lower.startswith("icews"):
        return "backend"
    if lower.startswith("ice_studio.orchestrator") or "orchestrator" in lower or "dispatcher" in lower:
        return "backend"
    if lower.startswith("ice_studio.storage"):
        return "backend"
    if lower.startswith("ice_studio.agents"):
        return "backend"
    if "llm" in lower:
        return "llm"
    return "runtime"


class LoggerBridge:
    def __init__(self, name: str):
        self.name = name
        self.domain = _infer_domain(name)
        self.owner = name.split(".")[-1] if name else "core"
        self.scope = name or "core"

    def _emit(
        self,
        level: str,
        msg: Any,
        *args: Any,
        extra: Optional[Dict[str, Any]] = None,
        exc_info: bool | BaseException | None = None,
    ) -> None:
        text = _format_message(msg, args)
        data = dict(extra or {})
        if exc_info:
            data["exception"] = traceback.format_exc()
        emit(
            LogEvent(
                LogEvent.now(),
                level,
                self.domain,
                self.owner,
                self.scope,
                text,
                data or None,
                None,
            )
        )

    def debug(self, msg: Any, *args: Any, **kwargs: Any) -> None:
        self._emit("DEBUG", msg, *args, **kwargs)

    def info(self, msg: Any, *args: Any, **kwargs: Any) -> None:
        self._emit("INFO", msg, *args, **kwargs)

    def warning(self, msg: Any, *args: Any, **kwargs: Any) -> None:
        self._emit("WARN", msg, *args, **kwargs)

    def warn(self, msg: Any, *args: Any, **kwargs: Any) -> None:
        self._emit("WARN", msg, *args, **kwargs)

    def error(self, msg: Any, *args: Any, **kwargs: Any) -> None:
        self._emit("ERROR", msg, *args, **kwargs)

    def exception(self, msg: Any, *args: Any, **kwargs: Any) -> None:
        kwargs.setdefault("exc_info", True)
        self._emit("ERROR", msg, *args, **kwargs)

    def critical(self, msg: Any, *args: Any, **kwargs: Any) -> None:
        self._emit("FATAL", msg, *args, **kwargs)

    def log(self, level: str, msg: Any, *args: Any, **kwargs: Any) -> None:
        upper = str(level).upper()
        if upper == "WARNING":
            upper = "WARN"
        self._emit(upper, msg, *args, **kwargs)

    def setLevel(self, _level: Any) -> None:
        return None


def get_logger(name: str) -> LoggerBridge:
    return LoggerBridge(name)
