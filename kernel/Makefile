# ===============================
# YAI Kernel Build System (L0+L1)
# ===============================

CC ?= cc

# ---- Repo root (kernel/ is one level down) ----
ROOT_DIR := $(abspath ..)

# ---- Unified repo-local layout ----
BUILD_DIR ?= $(ROOT_DIR)/build/kernel
BIN_DIR   ?= $(ROOT_DIR)/dist/bin

LOG_DIR   := $(ROOT_DIR)/dist/logs
TMP_DIR   := $(ROOT_DIR)/dist/tmp
CACHE_DIR := $(ROOT_DIR)/dist/cache

CFLAGS  ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
LDFLAGS ?=

# ---- Include paths ----
INCLUDES := \
	-I./include \
	-I$(ROOT_DIR)/boot/include \
	-I$(ROOT_DIR)/core/include \
	-I$(ROOT_DIR)/law/specs \
	-I$(ROOT_DIR)/law/specs/protocol \
	-I$(ROOT_DIR)/law/specs/protocol/runtime \
	-I$(ROOT_DIR)/law/specs/vault

# -----------------------------
# L0 Boot sources
# -----------------------------
BOOT_SRC := \
	$(ROOT_DIR)/boot/src/bootstrap.c \
	$(ROOT_DIR)/boot/src/preboot.c

# -----------------------------
# L1 Kernel sources
# -----------------------------
KERNEL_SRC := \
	src/enforcement/enforcement.c \
	src/core/fsm.c \
	src/core/ids.c \
	src/core/logger.c \
	src/core/project_tree.c \
	src/core/transport.c \
	src/core/yai_session.c \
	src/core/rpc_binary.c \
	src/core/rpc_codec.c \
	src/bin/workspace_kernel_main.c

# -----------------------------
# External shared sources
# -----------------------------
PROTOCOL_RUNTIME_SRC := $(ROOT_DIR)/law/specs/protocol/runtime/rpc_runtime.c
CORE_CONTROL_SRC     := $(ROOT_DIR)/core/src/control_transport.c

# -----------------------------
# Objects
# -----------------------------
OBJS_BOOT   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(BOOT_SRC))
OBJS_KERNEL := $(patsubst %.c,$(BUILD_DIR)/%.o,$(KERNEL_SRC))

PROTOCOL_RUNTIME_OBJ := $(BUILD_DIR)/protocol_runtime.o
CORE_CONTROL_OBJ     := $(BUILD_DIR)/control_transport.o

TARGET_KERNEL := $(BIN_DIR)/yai-kernel

.PHONY: all dirs abi kernel root clean purge

# ===============================
# Main
# ===============================
all: dirs abi kernel root
	@echo "--- [YAI-KERNEL] Build Complete ---"

abi:
	@test -f $(ROOT_DIR)/law/specs/vault/yai_vault_abi.h || \
	 (echo "ERROR: Missing yai_vault_abi.h"; exit 1)

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(LOG_DIR) $(TMP_DIR) $(CACHE_DIR)

kernel: $(TARGET_KERNEL)

$(TARGET_KERNEL): $(OBJS_BOOT) $(OBJS_KERNEL) $(PROTOCOL_RUNTIME_OBJ) $(CORE_CONTROL_OBJ)
	@echo "[LINK] $@"
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@ $(LDFLAGS)

# -----------------------------
# Root Control Plane (delegated)
# -----------------------------
root:
	@echo "[DELEGATE] building root control plane..."
	@$(MAKE) -C $(ROOT_DIR)/core \
		OUT_BIN_DIR=$(BIN_DIR) \
		OUT_BUILD_DIR=$(BUILD_DIR)/core

# -----------------------------
# Explicit build rules
# -----------------------------
$(PROTOCOL_RUNTIME_OBJ): $(PROTOCOL_RUNTIME_SRC)
	@echo "[CC] $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(CORE_CONTROL_OBJ): $(CORE_CONTROL_SRC)
	@echo "[CC] $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# -----------------------------
# Generic rule
# -----------------------------
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET_KERNEL)
	@echo "--- [YAI-KERNEL] Cleaned ---"

purge: clean
	@rm -rf $(BIN_DIR) $(LOG_DIR) $(TMP_DIR) $(CACHE_DIR)

-include $(OBJS_BOOT:.o=.d)
-include $(OBJS_KERNEL:.o=.d)
-include $(PROTOCOL_RUNTIME_OBJ:.o=.d)
-include $(CORE_CONTROL_OBJ:.o=.d)
