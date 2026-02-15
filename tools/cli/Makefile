# ==========================================
# YAI CLI Build System (Stable)
# ==========================================

CC := gcc

# ---- Artifact roots ----
ART_ROOT ?= $(HOME)/.yai/artifacts/yai-core

OUT_BUILD_DIR ?=
OUT_BIN_DIR ?=

BUILD_DIR := $(if $(OUT_BUILD_DIR),$(OUT_BUILD_DIR),$(ART_ROOT)/build/cli)
BIN_DIR   := $(if $(OUT_BIN_DIR),$(OUT_BIN_DIR),$(ART_ROOT)/bin)

TARGET := $(BIN_DIR)/yai

# ---- Include roots ----
LAW_DIR := ../../law/specs

CFLAGS := -Wall -Wextra -O2 -MMD -MP \
          -I./include \
          -I$(LAW_DIR)

LDFLAGS :=

# ---- Explicit Sources ----
SRCS := \
    src/main.c \
    src/cmd_dispatch.c \
    src/cmd_engine.c \
    src/cmd_kernel.c \
    src/cmd_mind.c \
    src/cmd_root.c \
    src/cmd_ws.c \
    src/cmd_law.c \
    src/cmd_test.c \
    src/cmd_up.c \
    src/env.c \
    src/fmt.c \
    src/paths.c \
    src/rpc.c

# ---- Objects ----
OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# ---- Phony targets ----
.PHONY: all clean dirs

# ==========================================
# Main build target
# ==========================================
all: dirs $(TARGET)
	@echo "--- [YAI-CLI] Build Complete ---"

# ---- Directories ----
dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# ---- Link CLI ----
$(TARGET): $(OBJS)
	@echo "[LINK] CLI: $@"
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# ---- Compile objects ----
$(BUILD_DIR)/%.o: src/%.c | dirs
	@mkdir -p $(dir $@)
	@echo "CC $<"
	$(CC) $(CFLAGS) -c $< -o $@

# ==========================================
# Clean
# ==========================================
clean:
	@echo "[CLEAN] CLI build..."
	rm -rf $(BUILD_DIR) $(TARGET)

# ---- Auto deps ----
-include $(OBJS:.o=.d)
