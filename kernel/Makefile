# ===============================
# YAI Kernel Build System (L0+L1)
# ===============================

CC ?= cc

# ---- Artifact root ----
ART_ROOT  ?= $(HOME)/.yai/artifacts/yai-core
BUILD_DIR ?= $(ART_ROOT)/build/kernel
BIN_DIR   ?= $(ART_ROOT)/bin
LOG_DIR   ?= $(ART_ROOT)/logs
TMP_DIR   ?= $(ART_ROOT)/tmp
CACHE_DIR ?= $(ART_ROOT)/cache

# ---- Compiler flags ----
CFLAGS  ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
LDFLAGS ?=

# ---- Include paths ----
INCLUDES := \
	-I./include \
	-I../boot/include \
	-I../core/include \
	-I../law/specs \
	-I../law/specs/protocol \
	-I../law/specs/vault

# -----------------------------
# Source files (L0: Boot)
# -----------------------------
BOOT_SRC := \
	../boot/src/bootstrap.c \
	../boot/src/preboot.c

# -----------------------------
# Source files (L1: Kernel)
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
# Core shim required by kernel
# -----------------------------
CORE_CONTROL_SRC := ../core/src/control_transport.c
CORE_CONTROL_OBJ := $(BUILD_DIR)/../core/src/control_transport.o

# -----------------------------
# Objects
# -----------------------------
OBJS_BOOT   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(BOOT_SRC))
OBJS_KERNEL := $(patsubst %.c,$(BUILD_DIR)/%.o,$(KERNEL_SRC))

# Kernel binary
TARGET_KERNEL := $(BIN_DIR)/yai-kernel

# -----------------------------
# Phony targets
# -----------------------------
.PHONY: all dirs abi kernel root clean purge

all: dirs abi kernel root
	@echo "--- [YAI] Build Complete (kernel + root) ---"

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

# -----------------------------
# Build kernel (L0+L1)
# -----------------------------
kernel: $(TARGET_KERNEL)

$(TARGET_KERNEL): $(OBJS_BOOT) $(OBJS_KERNEL) $(CORE_CONTROL_OBJ)
	@echo "[LINK] $@"
	@mkdir -p $(dir $@)
	$(CC) $(OBJS_BOOT) $(OBJS_KERNEL) $(CORE_CONTROL_OBJ) -o $@ $(LDFLAGS)

# -----------------------------
# Build Root Control Plane (delegated to ../core)
# -----------------------------
root:
	@echo "[DELEGATE] building root control plane in ../core ..."
	@$(MAKE) -C ../core

# -----------------------------
# Explicit build rule for core shim (no ambiguity)
# -----------------------------
$(CORE_CONTROL_OBJ): $(CORE_CONTROL_SRC)
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	$(CC) $(CFLAGS) $(INCLUDES) $(EXTRA_CFLAGS) -c $< -o $@

# -----------------------------
# Generic rule for building objects (boot + kernel)
# -----------------------------
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	$(CC) $(CFLAGS) $(INCLUDES) $(EXTRA_CFLAGS) -c $< -o $@

# -----------------------------
# Cleaning
# -----------------------------
clean:
	@echo "[CLEAN] kernel build..."
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET_KERNEL)

purge: clean
	@rm -rf $(BIN_DIR) $(LOG_DIR) $(TMP_DIR) $(CACHE_DIR)

# -----------------------------
# Auto-dependencies
# -----------------------------
-include $(OBJS_BOOT:.o=.d)
-include $(OBJS_KERNEL:.o=.d)
-include $(CORE_CONTROL_OBJ:.o=.d)
