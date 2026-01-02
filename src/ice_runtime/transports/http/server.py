from __future__ import annotations

import json
from http.server import BaseHTTPRequestHandler, HTTPServer
from typing import Any

from ice_runtime.logging import get_logger
from ice_api.ui.dispatcher import dispatch
from ice_runtime.runtime.runtime import get_runtime  # o come lo chiami tu

logger = get_logger("runtime", "http", "HttpServer")


class IceHttpHandler(BaseHTTPRequestHandler):

    def _json(self, status: int, payload: dict[str, Any]) -> None:
        body = json.dumps(payload).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def _read_body(self) -> dict[str, Any]:
        length = int(self.headers.get("Content-Length", "0"))
        if length == 0:
            return {}
        raw = self.rfile.read(length)
        return json.loads(raw.decode("utf-8"))

    def do_GET(self) -> None:
        try:
            request = self._build_request()
            result = dispatch(request, get_runtime())
            self._json(200, result)
        except Exception as exc:
            logger.exception("HTTP GET failed", exc_info=exc)
            self._json(500, {"ok": False, "error": str(exc)})

    def do_POST(self) -> None:
        try:
            request = self._build_request(with_body=True)
            result = dispatch(request, get_runtime())
            self._json(200, result)
        except Exception as exc:
            logger.exception("HTTP POST failed", exc_info=exc)
            self._json(500, {"ok": False, "error": str(exc)})

    def _build_request(self, with_body: bool = False) -> dict[str, Any]:
        body = self._read_body() if with_body else {}

        # mapping HTTP → API action
        if self.path.rstrip("/") == "/system/status":
            return {"action": "system.status"}

        if self.path.rstrip("/") == "/system/start":
            return {"action": "system.start"}

        # fallback generico (API future)
        return {
            "action": body.get("action"),
            "params": body.get("params", {}),
        }


def main() -> None:
    server = HTTPServer(("127.0.0.1", 7030), IceHttpHandler)
    logger.info("HTTP server listening", extra={"port": 7030})
    server.serve_forever()


if __name__ == "__main__":
    main()
