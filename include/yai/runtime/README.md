# Runtime Public Headers (Legacy Migration Source)

`include/yai/runtime/*` is retained as migration source while moving canonical
operational-domain semantics to `include/yai/container/*`.

Canonical model:
- container is the operational domain
- workspace is legacy vocabulary only
- kernel owns privileged roots (containment/session admission/grants validity)
