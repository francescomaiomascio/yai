from .base import LogTransport
from ..event import LogEvent
from ..runtime import RuntimeContext
from ..router import resolve_log_path


class FileSystemTransport(LogTransport):
    """
    Writes log events to JSONL files under the runtime base directory.
    """

    def __init__(self, ctx: RuntimeContext):
        self.ctx = ctx
        self.ctx.base_dir.mkdir(parents=True, exist_ok=True)

    def send(self, event: LogEvent) -> None:
        try:
            phase = (self.ctx.phase or "preboot").lower()
            domain = (event.domain or "").lower()
            owner = (event.owner or "").lower()
            if phase == "preboot":
                if domain == "backend" and owner != "preboot":
                    return
                if domain not in {"preboot", "ui", "icenet", "backend"}:
                    return
            elif phase == "runtime":
                if domain == "preboot":
                    return
                if domain == "backend" and owner == "preboot":
                    return
            rel_path = resolve_log_path(event, self.ctx)
            path = self.ctx.base_dir / rel_path
            path.parent.mkdir(parents=True, exist_ok=True)
            with path.open("a", encoding="utf-8") as handle:
                handle.write(event.to_json() + "\n")
        except Exception:
            return
