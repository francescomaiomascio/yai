# ===============================
# YAI Kernel Build System (L0+L1+Root)
# ===============================

CC := gcc

# ---- Artifact root ----
ART_ROOT ?= $(HOME)/.yai/artifacts/yai-core

BUILD_DIR ?= $(ART_ROOT)/build/kernel
BIN_DIR   ?= $(ART_ROOT)/bin
LOG_DIR   ?= $(ART_ROOT)/logs
TMP_DIR   ?= $(ART_ROOT)/tmp
CACHE_DIR ?= $(ART_ROOT)/cache

# ---- Compiler flags ----
CFLAGS := -Wall -Wextra -O2 -MMD -MP \
          -I./include \
          -I../boot/include \
          -I../law/specs \
          -I../law/specs/protocol \
          -I../law/specs/vault

LDFLAGS :=

# -----------------------------
# Source files
# -----------------------------
# Root server specific
ROOT_CFLAGS := $(CFLAGS) -I./include -I../include
$(BUILD_DIR)/src/bin/yai_root_server.o: src/bin/yai_root_server.c
	@mkdir -p $(dir $@)
	$(CC) $(ROOT_CFLAGS) -c $< -o $@

# L0: Boot / Ignition
BOOT_SRC := \
    ../boot/src/bootstrap.c \
    ../boot/src/preboot.c

# L1: Kernel core
KERNEL_CORE_SRC := \
    src/enforcement/enforcement.c \
    src/core/fsm.c \
    src/core/ids.c \
    src/core/logger.c \
    src/core/project_tree.c \
    src/core/transport.c \
    src/core/yai_session.c \
    src/core/control_transport.c \
    src/core/rpc_binary.c \
    src/bin/workspace_kernel_main.c

# L0+L1 unified kernel
SRCS_KERNEL := $(BOOT_SRC) $(KERNEL_CORE_SRC)
OBJS_KERNEL := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS_KERNEL))
TARGET_KERNEL := $(BIN_DIR)/yai-kernel

# -----------------------------
# Root Control Plane (Persistent)
# -----------------------------
ROOT_SRC := \
    src/bin/yai_root_server.c \
    src/core/control_transport.c \
    src/core/yai_session.c \
    src/core/rpc_binary.c \
    src/enforcement/enforcement.c

OBJS_ROOT := $(patsubst %.c,$(BUILD_DIR)/%.o,$(ROOT_SRC))
TARGET_ROOT := $(BIN_DIR)/yai-root-server

# -----------------------------
# Phony targets
# -----------------------------
.PHONY: all clean purge dirs abi kernel root

all: dirs abi kernel root
	@echo "--- [YAI-KERNEL] Build Complete (L0+L1+Root) ---"

# -----------------------------
# ABI guard
# -----------------------------
abi:
	@test -f ../law/specs/vault/yai_vault_abi.h || \
	(echo "ERROR: Missing yai_vault_abi.h. Run scripts/gen-vault-abi"; exit 1)

# -----------------------------
# Create directories
# -----------------------------
dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(LOG_DIR) $(TMP_DIR) $(CACHE_DIR)
	@mkdir -p $(BUILD_DIR)/../boot/src  # Per oggetti boot

# -----------------------------
# Build kernel (L0+L1)
# -----------------------------
kernel: $(TARGET_KERNEL)

$(TARGET_KERNEL): $(OBJS_KERNEL)
	@echo "[LINK] yai-kernel..."
	@mkdir -p $(dir $@)
	$(CC) $(OBJS_KERNEL) -o $@ $(LDFLAGS)

# -----------------------------
# Build Root Control Plane
# -----------------------------
root: $(TARGET_ROOT)

$(TARGET_ROOT): $(OBJS_ROOT)
	@echo "[LINK] yai-root-server..."
	@mkdir -p $(dir $@)
	$(CC) $(OBJS_ROOT) -o $@ $(LDFLAGS)

# -----------------------------
# Generic rule for building objects
# -----------------------------
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

# -----------------------------
# Cleaning
# -----------------------------
clean:
	@echo "[CLEAN] Kernel build..."
	rm -rf $(BUILD_DIR)

purge: clean
	rm -rf $(BIN_DIR) $(LOG_DIR) $(TMP_DIR) $(CACHE_DIR)

# -----------------------------
# Auto-dependencies
# -----------------------------
-include $(OBJS_KERNEL:.o=.d)
-include $(OBJS_ROOT:.o=.d)
