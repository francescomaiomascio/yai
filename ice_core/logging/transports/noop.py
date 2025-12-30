from .base import LogTransport


class NoopTransport(LogTransport):
    def send(self, event):
        return None
