# K-8 skeleton makefile for YAI kernel path.

CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -Ikernel/include -Ikernel

KERNEL_CORE_SRCS := \
	kernel/core/kernel.c \
	kernel/lifecycle/lifecycle_state.c \
	kernel/lifecycle/readiness.c \
	kernel/lifecycle/transitions.c \
	kernel/state/kernel_state.c \
	kernel/registry/kernel_registry.c \
	kernel/registry/container_registry.c \
	kernel/registry/session_registry.c \
	kernel/registry/capability_registry.c \
	kernel/registry/containment_registry.c \
	kernel/registry/trace_registry.c \
	kernel/registry/grants_registry.c \
	kernel/policy/capabilities.c \
	kernel/policy/policy_hooks.c \
	kernel/grants/grant_state.c \
	kernel/grants/grant_checks.c \
	kernel/grants/grant_lifecycle.c \
	kernel/session/session_admission.c \
	kernel/session/session_state.c \
	kernel/session/session_registry.c \
	kernel/security/containment.c \
	kernel/container/namespaces.c \
	kernel/container/rootfs.c \
	kernel/container/mounts.c \
	kernel/container/limits.c \
	kernel/init/bootstrap.c

.PHONY: all
all:
	@echo "YAI kernel lifecycle core initialized (K-8)."

.PHONY: check
check:
	$(CC) $(CFLAGS) -fsyntax-only $(KERNEL_CORE_SRCS)
