# =========================================
# YAI — Core (Root Control Plane) Makefile
# =========================================

CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -O2 -std=c11
LDFLAGS ?= 

# Path passati dal Root Makefile o default
OUT_BIN_DIR   ?= ../artifacts/bin
OUT_BUILD_DIR ?= ../artifacts/build/core
INCLUDES      := -I./include -I../kernel/include -I../law/specs

# Target Binary
TARGET := $(OUT_BIN_DIR)/yai-root-server

# Sorgenti
SRCS := src/yai_root_server.c \
        src/control_transport.c

# Oggetti
OBJS := $(SRCS:src/%.c=$(OUT_BUILD_DIR)/%.o)

.PHONY: all clean prep

all: prep $(TARGET)

# Creazione directory di build
prep:
	@mkdir -p $(OUT_BIN_DIR)
	@mkdir -p $(OUT_BUILD_DIR)

# Link finale
$(TARGET): $(OBJS)
	@echo "[CORE] Linking $@..."
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "✔ Root Control Plane built."

# Compilazione oggetti
$(OUT_BUILD_DIR)/%.o: src/%.c
	@echo "[CORE] Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(EXTRA_CFLAGS) -c $< -o $@

clean:
	@echo "[CORE] Cleaning..."
	@rm -rf $(OUT_BUILD_DIR)
	@rm -f $(TARGET)