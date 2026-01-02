from __future__ import annotations

import asyncio
import json
import os
import logging
import http

import websockets
from websockets.exceptions import ConnectionClosedOK, ConnectionClosedError
from websockets.server import ServerConnection
from websockets.http11 import Request

from ice_runtime.logging import get_logger
from ice_api.ui.dispatcher import dispatch
from ice_runtime.runtime.runtime import get_runtime

logger = get_logger("runtime", "ws", "WebSocketServer")


class IceWSServer:
    def __init__(self, host="127.0.0.1", port: int | None = None):
        self.host = host
        self.port = port or int(os.getenv("ICE_WS_PORT", "7031"))
        self.server = None

    async def _reject_http(self, connection: ServerConnection, request: Request):
        upgrade = request.headers.get("Upgrade")
        if upgrade and upgrade.lower() == "websocket":
            return None
        return connection.protocol.reject(
            http.HTTPStatus.BAD_REQUEST,
            "WebSocket endpoint\n",
        )

    async def start(self):
        logger.info("Starting WebSocket server", extra={"port": self.port})

        self.server = await websockets.serve(
            self._handler,
            self.host,
            self.port,
            process_request=self._reject_http,
            ping_interval=20,
            ping_timeout=20,
            max_size=10_000_000,
        )

        await asyncio.Future()  # run forever

    async def _handler(self, websocket, *args):
        path = self._extract_path(websocket, args)
        logger.info("WS client connected", extra={"path": path})

        async def emit_event(event: dict):
            try:
                await websocket.send(json.dumps(event))
            except Exception as exc:
                logger.exception("WS emit failed", exc_info=exc)

        try:
            async for raw in websocket:
                try:
                    request = json.loads(raw)
                except Exception:
                    logger.warning("Invalid WS JSON")
                    continue

                result = await dispatch(
                    request=request,
                    runtime=get_runtime(),
                    emit_event=emit_event,
                    transport="ws",
                    channel=path,
                )

                if result is not None:
                    await websocket.send(json.dumps(result))

        except ConnectionClosedOK:
            logger.info("WS client closed", extra={"path": path})
        except ConnectionClosedError:
            logger.warning("WS client disconnected", extra={"path": path})

    def _extract_path(self, websocket, args) -> str:
        path = "/"
        if hasattr(websocket, "request"):
            try:
                path = websocket.request.path
            except Exception:
                pass
        if path == "/" and len(args) == 1:
            path = args[0]
        return str(path).rstrip("/") or "/"
