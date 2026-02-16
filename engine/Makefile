# ===============================
# YAI Engine Build System (L2)
# ===============================

CC := gcc

# ---- Repo root inferred from engine/ ----
ROOT_DIR := $(abspath ..)

# ---- Unified build layout (repo-local) ----
BUILD_DIR ?= $(ROOT_DIR)/build/engine
BIN_DIR   ?= $(ROOT_DIR)/dist/bin

LOG_DIR   := $(ROOT_DIR)/dist/logs
TMP_DIR   := $(ROOT_DIR)/dist/tmp
CACHE_DIR := $(ROOT_DIR)/dist/cache

# ---- ABI + Protocol source of truth ----
VAULT_ABI_SRC := $(ROOT_DIR)/law/specs/vault/yai_vault_abi.h
PROTOCOL_DIR  := $(ROOT_DIR)/law/specs/protocol
PROTOCOL_RUNTIME_DIR := $(ROOT_DIR)/law/specs/protocol/runtime

# ---- Source roots ----
SRC_DIR := src
THIRD_PARTY_DIR := third_party

# ---- Engine sources ----
ENGINE_SRCS := $(shell find $(SRC_DIR) -name "*.c")
ENGINE_SRCS += $(THIRD_PARTY_DIR)/cjson/cJSON.c

# ---- Protocol runtime ----
PROTOCOL_RUNTIME_SRCS := \
	$(PROTOCOL_RUNTIME_DIR)/rpc_runtime.c

# ---- Objects ----
OBJS_ENGINE  := $(patsubst %.c,$(BUILD_DIR)/%.o,$(ENGINE_SRCS))
OBJS_PROTO   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(PROTOCOL_RUNTIME_SRCS))

OBJS := $(OBJS_ENGINE) $(OBJS_PROTO)

# ---- Compiler flags ----
CFLAGS := -Wall -Wextra -O2 -std=c11 -MMD -MP \
          -I./include \
          -I./third_party/cjson \
          -I$(ROOT_DIR)/kernel/include \
          -I$(ROOT_DIR)/law/specs \
          -I$(PROTOCOL_DIR) \
          -I$(PROTOCOL_RUNTIME_DIR) \
          -I$(ROOT_DIR)/law/specs/vault

LDFLAGS := -lpthread -lsqlite3

TARGET := $(BIN_DIR)/yai-engine
TEST_CORTEX := $(BUILD_DIR)/cortex_harness

.PHONY: all clean purge dirs debug test-cortex abi

# ===============================
# Main targets
# ===============================

all: abi dirs $(TARGET)

abi:
	@test -f $(VAULT_ABI_SRC) || \
	 (echo "ERROR: Missing yai_vault_abi.h"; exit 1)

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(LOG_DIR) $(TMP_DIR) $(CACHE_DIR)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "--- [YAI-ENGINE] Build Complete ---"

$(BUILD_DIR)/%.o: %.c | dirs
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test-cortex: abi dirs $(TEST_CORTEX)
	@$(TEST_CORTEX)

$(TEST_CORTEX): tests/cortex_harness.c src/cortex/engine_cortex.c | dirs
	$(CC) $(CFLAGS) tests/cortex_harness.c src/cortex/engine_cortex.c -o $(TEST_CORTEX)

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -rf $(BUILD_DIR)
	@echo "--- [YAI-ENGINE] Cleaned Build ---"

purge: clean
	rm -rf $(BIN_DIR) $(LOG_DIR) $(TMP_DIR) $(CACHE_DIR)

-include $(OBJS_ENGINE:.o=.d)
-include $(OBJS_PROTO:.o=.d)
