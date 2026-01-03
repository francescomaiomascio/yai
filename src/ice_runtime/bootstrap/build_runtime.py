from __future__ import annotations

import asyncio
import os
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional

# ---------------------------------------------------------------------
# CONFIG
# ---------------------------------------------------------------------
from engine.config import ConfigLoader, ConfigManager
config_mgr = ConfigManager(ConfigLoader())

# ---------------------------------------------------------------------
# LOGGING (PASSIVO)
# ---------------------------------------------------------------------
from ice_runtime.logging import get_logger
logger = get_logger("engine", "orchestrator", "runtime_builder")

# ---------------------------------------------------------------------
# API
# ---------------------------------------------------------------------
from engine.api.registry import ApiRegistry
from engine.api.spec import ActionSpec, AgentSpec, build_default_actions
from engine.api.types import ActionDomain, AgentName, ActionCall

# ---------------------------------------------------------------------
# AGENT RUNTIME
# ---------------------------------------------------------------------
from engine.agents.base.agent_registry import AgentRegistry
from engine.agents.base.agent_task import AgentTask
from engine.agents.runtime.agent_runner import AgentRunner, AgentRunnerConfig
from engine.agents.runtime.agent_scheduler import AgentScheduler, AgentSchedulerConfig
from engine.agents.runtime.agent_events import AgentEventBus

# Domain agents
from engine.agents.domain.log_agent import LogAgent
from engine.agents.domain.scanner_agent import ScannerAgent
from engine.agents.domain.analyzer_agent import AnalyzerAgent
from engine.agents.domain.validator_agent import ValidatorAgent
from engine.agents.domain.planner_agent import PlannerAgent
from engine.agents.domain.project_agent import ProjectAgent
from engine.agents.domain.knowledge_agent import KnowledgeAgent
from engine.agents.domain.knowledge_sync_agent import KnowledgeSyncAgent
from engine.agents.domain.historian_agent import HistorianAgent
from engine.agents.domain.refactor_agent import RefactorAgent
from engine.agents.domain.git_agent import GitAgent
from engine.agents.domain.code_agent import CodeAgent
from engine.agents.domain.system_agent import SystemAgent

from engine.agents.llm_agents.llm_router_agent import LLMRouterAgent
from engine.agents.llm_agents.code_model_agent import CodeModelAgent
from engine.agents.codemodel.loader import get_global_codemodel

# ---------------------------------------------------------------------
# LLM / EMBEDDINGS
# ---------------------------------------------------------------------
from engine.llm.adapter import UnifiedLLMAdapter, get_default_adapter
from engine.embeddings.adapter import UnifiedEmbeddingAdapter, get_default_embedding_adapter
from engine.llm.types import LLMMessage

# ---------------------------------------------------------------------
# ORCHESTRATOR
# ---------------------------------------------------------------------
from engine.orchestrator.orchestrator import Orchestrator, OrchestratorConfig
from engine.orchestrator.router import RouterConfig
from engine.orchestrator.dispatcher import DispatcherConfig
from engine.orchestrator.middleware.tracing import tracing_middleware
from engine.orchestrator.middleware.logging import logging_middleware

# ---------------------------------------------------------------------
# SESSION / STORAGE
# ---------------------------------------------------------------------
from engine.storage.session.manager import SessionManager
from engine.storage.session.lifecycle import get_default_hooks
from engine.storage.session.context import SessionContext, _LightweightSessionContext
from engine.storage.base import BackendConfig, BackendType, StorageMode

# ---------------------------------------------------------------------
# RUNTIME CONTAINER
# ---------------------------------------------------------------------
@dataclass
class CortexRuntime:
    orchestrator: Orchestrator
    api_registry: ApiRegistry
    agent_registry: AgentRegistry
    agent_runner: AgentRunner
    agent_scheduler: AgentScheduler
    agent_event_bus: AgentEventBus
    llm_adapter: UnifiedLLMAdapter
    embedding_adapter: UnifiedEmbeddingAdapter
    session_manager: SessionManager
    config: Dict[str, Any]

# =====================================================================
# BUILDERS
# =====================================================================

def build_api_registry() -> ApiRegistry:
    registry = ApiRegistry()
    actions = build_default_actions()
    registry.register_actions(actions)

    by_agent: dict[str, list[ActionSpec]] = {}
    domains: dict[str, set[ActionDomain]] = {}

    for action in actions:
        if not action.owner_agent:
            continue
        by_agent.setdefault(action.owner_agent, []).append(action)
        domains.setdefault(action.owner_agent, set()).add(action.domain)

    for agent_name, acts in by_agent.items():
        registry.register_agent(
            AgentSpec(
                name=agent_name,
                description=f"Auto-generated AgentSpec for {agent_name}",
                actions=[a.name for a in acts],
                capabilities=[],
                main_domain=list(domains[agent_name])[0],
            )
        )

    return registry


def build_agent_runtime() -> tuple[AgentRegistry, AgentRunner, AgentScheduler, AgentEventBus]:
    registry = AgentRegistry()
    bus = AgentEventBus()

    def reg(agent):
        registry.register(agent)

    code_model = get_global_codemodel()

    reg(LogAgent())
    reg(ScannerAgent())
    reg(AnalyzerAgent())
    reg(ValidatorAgent())
    reg(PlannerAgent())
    reg(ProjectAgent())
    reg(KnowledgeAgent())
    reg(KnowledgeSyncAgent())
    reg(HistorianAgent())
    reg(RefactorAgent())
    reg(GitAgent())
    reg(CodeAgent(model=code_model))
    reg(CodeModelAgent(code_model=code_model))
    reg(SystemAgent())
    reg(LLMRouterAgent())

    runner = AgentRunner(
        registry=registry,
        event_bus=bus,
        config=AgentRunnerConfig(),
    )

    scheduler = AgentScheduler(
        runner=runner,
        event_bus=bus,
        config=AgentSchedulerConfig(),
    )

    return registry, runner, scheduler, bus


def build_orchestrator(api_registry: ApiRegistry) -> Orchestrator:
    router_cfg = RouterConfig(
        default_agent_by_domain={
            spec.main_domain: spec.name
            for spec in api_registry.list_agents()
            if spec.main_domain
        },
        fallback_agent="llm-router-agent",
    )

    orch = Orchestrator(
        registry=api_registry,
        config=OrchestratorConfig(
            router=router_cfg,
            dispatcher=DispatcherConfig(),
        ),
    )

    orch.middleware.add(tracing_middleware)
    orch.middleware.add(logging_middleware)
    return orch


# =====================================================================
# ENTRYPOINT
# =====================================================================

def create_runtime_from_config(config: Dict[str, Any]) -> CortexRuntime:
    logger.info("Creating CortexRuntime")

    api_registry = build_api_registry()

    llm_adapter = get_default_adapter(config_mgr.get("llm"))
    embedding_adapter = get_default_embedding_adapter(config_mgr.get("embeddings"))

    agent_registry, agent_runner, agent_scheduler, event_bus = build_agent_runtime()

    orchestrator = build_orchestrator(api_registry)

    # Wire agent runners
    for agent in agent_registry.list_agents():
        async def runner(call: ActionCall, spec: ActionSpec, name=agent.name):
            session = SessionContext.current()
            if session is None:
                raise RuntimeError("No active SessionContext")

            task = AgentTask(kind=call.name, payload=call.params, label=call.name)
            result = await agent_runner.run(
                agent_name=name,
                task=task,
                session=session,
                correlation_id=getattr(call, "request_id", None),
            )
            return result.payload or {}

        orchestrator.dispatcher.register_runner(agent.name, runner)

    # Session manager
    base_path = Path(
        os.getenv("ICE_STUDIO_HOME", Path.home() / ".ice_studio" / "workspaces")
    ).expanduser()

    session_manager = SessionManager(
        base_path=base_path,
        default_backend_configs={
            "relational": BackendConfig.sqlite("data.db")
        },
        lifecycle_hooks=get_default_hooks(),
    )

    try:
        loop = asyncio.get_running_loop()
        loop.run_until_complete(session_manager.initialize())
    except RuntimeError:
        asyncio.run(session_manager.initialize())

    return CortexRuntime(
        orchestrator=orchestrator,
        api_registry=api_registry,
        agent_registry=agent_registry,
        agent_runner=agent_runner,
        agent_scheduler=agent_scheduler,
        agent_event_bus=event_bus,
        llm_adapter=llm_adapter,
        embedding_adapter=embedding_adapter,
        session_manager=session_manager,
        config=config,
    )
