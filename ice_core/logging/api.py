from .event import LogEvent
from .router import LogRouter

_router: LogRouter | None = None

def init(router: LogRouter):
    global _router
    _router = router

def is_initialized() -> bool:
    return _router is not None

def emit(event: LogEvent):
    if not _router:
        return
    if event.runtime_id is None:
        event = LogEvent(
            event.ts,
            event.level,
            event.domain,
            event.owner,
            event.scope,
            event.msg,
            event.data,
            _router.runtime.runtime_id,
        )
    _router.route(event)


def set_phase(phase: str) -> None:
    if not _router:
        return
    _router.runtime.set_phase(phase)

def info(domain, owner, scope, msg, data=None):
    emit(LogEvent(LogEvent.now(), "INFO", domain, owner, scope, msg, data, None))

def error(domain, owner, scope, msg, data=None):
    emit(LogEvent(LogEvent.now(), "ERROR", domain, owner, scope, msg, data, None))
