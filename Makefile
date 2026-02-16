# =========================================
# YAI — Root Build Orchestrator
# =========================================

ROOT_DIR  := $(abspath .)
BIN_DIR   := $(ROOT_DIR)/dist/bin
BUILD_DIR := $(ROOT_DIR)/build
DIST_DIR  := $(ROOT_DIR)/dist
VERIFY_DIR:= $(DIST_DIR)/verify

BOOT_DIR   := boot
CORE_DIR   := core
KERNEL_DIR := kernel
ENGINE_DIR := engine
MIND_DIR   := mind
CLI_DIR    := tools/cli

DOXYFILE := Doxyfile

.PHONY: all boot core kernel engine mind cli clean docs

# -----------------------------------------
# Build Order
# -----------------------------------------
all: boot core kernel engine mind cli
	@echo "--- [YAI] Build Complete ---"

# -----------------------------------------
# Boot
# -----------------------------------------
boot:
	$(MAKE) -C $(BOOT_DIR) \
	OUT_BIN_DIR=$(BIN_DIR) \
	OUT_BUILD_DIR=$(BUILD_DIR)/boot \
	EXTRA_CFLAGS="-I$(ROOT_DIR)/law/specs" all

# -----------------------------------------
# Core (Root Plane)
# -----------------------------------------
core:
	$(MAKE) -C $(CORE_DIR) \
	OUT_BIN_DIR=$(BIN_DIR) \
	OUT_BUILD_DIR=$(BUILD_DIR)/core \
	EXTRA_CFLAGS="-I$(ROOT_DIR)/law/specs" all

# -----------------------------------------
# Kernel
# -----------------------------------------
kernel:
	$(MAKE) -C $(KERNEL_DIR) \
	OUT_BIN_DIR=$(BIN_DIR) \
	OUT_BUILD_DIR=$(BUILD_DIR)/kernel \
	EXTRA_CFLAGS="-I$(ROOT_DIR)/law/specs" all

# -----------------------------------------
# Engine
# -----------------------------------------
engine:
	$(MAKE) -C $(ENGINE_DIR) \
	OUT_BIN_DIR=$(BIN_DIR) \
	OUT_BUILD_DIR=$(BUILD_DIR)/engine all

# -----------------------------------------
# Mind (Rust)
# -----------------------------------------
mind:
	cargo build --release --workspace
	@mkdir -p $(BIN_DIR)
	@cp target/release/yai-mind $(BIN_DIR)/yai-mind 2>/dev/null || true

# -----------------------------------------
# CLI
# -----------------------------------------
cli:
	$(MAKE) -C $(CLI_DIR) \
	OUT_BIN_DIR=$(BIN_DIR) \
	OUT_BUILD_DIR=$(BUILD_DIR)/cli

# -----------------------------------------
# Clean
# -----------------------------------------
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_DIR)
	cd $(MIND_DIR) && cargo clean || true

# -----------------------------------------
# Docs
# -----------------------------------------
docs:
	@mkdir -p dist/docs/doxygen
	@doxygen $(DOXYFILE)
	@echo "✔ Doxygen: dist/docs/doxygen/html/index.html"
