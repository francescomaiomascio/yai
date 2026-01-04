"""
ICE Runtime — Memory Views

Espone VISTE DERIVATE e FILTRATE delle memorie agli agenti.
Questo modulo NON permette accesso diretto alla memoria globale.

Principi:
- read-only
- policy-driven
- event-safe
- non omnisciente
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import List, Dict, Any, Iterable

from ice_runtime.memory.registry import MemoryRegistry
from ice_runtime.memory.lifecycle import MemoryLifecycleManager
from ice_runtime.memory.errors import MemoryAccessError
from ice_runtime.capabilities.enforcement import require_capability
from ice_runtime.capabilities.registry import CapabilityType


@dataclass(frozen=True)
class MemoryView:
    """
    Vista immutabile di una singola memoria.

    NON È una memoria.
    NON È persistente.
    """
    memory_id: str
    memory_type: str
    payload: Dict[str, Any]
    confidence: float
    provenance: Dict[str, Any]


class MemoryViewBuilder:
    """
    Costruisce viste di memoria per UN Run / UN Agente.

    Autorità:
    - Runtime only
    - policy enforced
    """

    def __init__(
        self,
        *,
        registry: MemoryRegistry,
        lifecycle: MemoryLifecycleManager,
    ) -> None:
        self._registry = registry
        self._lifecycle = lifecycle

    # =====================================================
    # PUBLIC API (Runtime-only)
    # =====================================================

    def build_view(
        self,
        *,
        run_id: str,
        agent_id: str,
        memory_ids: Iterable[str],
        max_items: int,
    ) -> List[MemoryView]:
        """
        Costruisce una vista filtrata per un agente.

        Richiede esplicitamente capability MEMORY_READ.
        """
        require_capability(
            run_id=run_id,
            capability_type=CapabilityType.MEMORY_READ,
        )

        views: List[MemoryView] = []

        for memory_id in memory_ids:
            if len(views) >= max_items:
                break

            view = self._build_single_view(
                run_id=run_id,
                agent_id=agent_id,
                memory_id=memory_id,
            )

            if view is not None:
                views.append(view)

        return views

    # =====================================================
    # INTERNAL
    # =====================================================

    def _build_single_view(
        self,
        *,
        run_id: str,
        agent_id: str,
        memory_id: str,
    ) -> MemoryView | None:
        # lifecycle check
        if not self._lifecycle.is_active(memory_id):
            return None

        memory = self._registry.get(memory_id)

        # policy enforcement (access_policy già validata a monte)
        if not memory.access_policy.is_allowed(agent_id):
            return None

        # payload filtering (NO dumping completo)
        filtered_payload = memory.access_policy.filter_payload(
            memory.payload
        )

        return MemoryView(
            memory_id=memory.memory_id,
            memory_type=memory.memory_type,
            payload=filtered_payload,
            confidence=memory.confidence,
            provenance=memory.provenance,
        )
