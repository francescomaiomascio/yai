# ===============================
# YAI Boot Build System (L0)
# ===============================

CC := gcc

# --------------------------------
# Output layout (repo-native)
# --------------------------------

OUT_BUILD_DIR ?=
OUT_BIN_DIR   ?=

BUILD_DIR := $(if $(OUT_BUILD_DIR),$(OUT_BUILD_DIR),../build/boot)
BIN_DIR   := $(if $(OUT_BIN_DIR),$(OUT_BIN_DIR),../dist/bin)

TARGET := $(BIN_DIR)/yai-boot

# --------------------------------
# Compiler flags
# --------------------------------

CFLAGS := -Wall -Wextra -O2 -std=c11 -MMD -MP \
          -I./include \
          -I../kernel/include \
          -I../law/specs \
          -I../law/specs/vault

LDFLAGS :=

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
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

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
