from dataclasses import dataclass
from typing import Any, Optional, Dict
from datetime import datetime
import json

@dataclass(frozen=True)
class LogEvent:
    ts: str
    level: str                # TRACE|DEBUG|INFO|WARN|ERROR|FATAL
    domain: str               # runtime, backend, ui, llm, icenet, audit
    owner: str                # es: dashboard, workspace-1, system-agent
    scope: str                # modulo / classe
    msg: str
    data: Optional[Dict[str, Any]]
    runtime_id: Optional[str]

    @staticmethod
    def now():
        return datetime.utcnow().isoformat()

    def to_json(self) -> str:
        return json.dumps(
            {
                "ts": self.ts,
                "level": self.level,
                "domain": self.domain,
                "owner": self.owner,
                "scope": self.scope,
                "msg": self.msg,
                "data": self.data,
                "runtime_id": self.runtime_id,
            }
        )
