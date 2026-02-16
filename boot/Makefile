# ===============================
# YAI Boot Build System (L0)
# ===============================

CC ?= cc

# ---- Repo root inferred from boot/ ----
ROOT_DIR := $(abspath ..)

# --------------------------------
# Orchestrator outputs (optional override)
# --------------------------------
OUT_BUILD_DIR ?= $(ROOT_DIR)/build/boot
OUT_BIN_DIR   ?= $(ROOT_DIR)/dist/bin

BUILD_DIR := $(OUT_BUILD_DIR)
BIN_DIR   := $(OUT_BIN_DIR)

TARGET := $(BIN_DIR)/yai-boot

# --------------------------------
# Externalized specs (submodule)
# --------------------------------
SPECS_DIR := $(ROOT_DIR)/deps/yai-specs

# --------------------------------
# Compiler flags
# --------------------------------
CFLAGS ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
CFLAGS += -I./include
CFLAGS += -I$(ROOT_DIR)/kernel/include
CFLAGS += -I$(SPECS_DIR)
CFLAGS += -I$(SPECS_DIR)/protocol
CFLAGS += -I$(SPECS_DIR)/protocol/runtime
CFLAGS += -I$(SPECS_DIR)/vault

LDFLAGS ?=

# --------------------------------
# Sources
# --------------------------------
SRCS := \
    src/preboot.c \
    src/bootstrap.c \
    src/yai_boot_main.c

OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# --------------------------------
# Phony targets
# --------------------------------
.PHONY: all clean dirs

# =================================
# Main target
# =================================
all: dirs $(TARGET)
	@echo "--- [YAI-BOOT] L0 Build Complete ---"

# --------------------------------
# Directories
# --------------------------------
dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# --------------------------------
# Link
# --------------------------------
$(TARGET): $(OBJS)
	@echo "[LINK] $@"
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# --------------------------------
# Compile
# --------------------------------
$(BUILD_DIR)/%.o: src/%.c | dirs
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

# --------------------------------
# Clean
# --------------------------------
clean:
	@echo "[CLEAN] Boot build..."
	@rm -rf $(BUILD_DIR)

# --------------------------------
# Auto deps
# --------------------------------
-include $(OBJS:.o=.d)
