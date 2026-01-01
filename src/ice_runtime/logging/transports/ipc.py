from .base import LogTransport


class IpcLogTransport(LogTransport):
    def __init__(self, sender):
        """
        sender: funzione pura (es. process.send)
        NON deve loggare.
        """
        self._sender = sender

    def send(self, event):
        try:
            self._sender({
                "type": "LOG_EVENT",
                "payload": event.__dict__,
            })
        except Exception:
            pass
