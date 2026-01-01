from abc import ABC, abstractmethod
from ..event import LogEvent


class LogTransport(ABC):
    """
    Trasporto puro.
    NON logga.
    NON fa retry.
    NON solleva errori.
    """

    @abstractmethod
    def send(self, event: LogEvent) -> None:
        ...
