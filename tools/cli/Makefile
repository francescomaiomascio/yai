# YAI CLI - Sovereign Makefile (ADR-004)
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I./include -I../../engine/src/external
LDFLAGS = 

# Directory di output
BIN_DIR = .
OBJ_DIR = obj

# Sorgenti della CLI
SRC = src/main.c \
      src/paths.c \
      src/rpc.c \
      src/envelope.c \
      src/fmt.c \
      src/env.c \
      src/cmd_root.c \
      src/cmd_kernel.c \
      src/cmd_ws.c \
      src/cmd_engine.c \
      src/cmd_mind.c \
      src/cmd_law.c

# Dipendenza esterna (cJSON dall'engine)
EXTERNAL_SRC = ../../engine/src/external/cJSON.c

# Generazione lista oggetti
OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/cJSON.o

# Target principale
TARGET = $(BIN_DIR)/yai

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking Sovereign CLI: $@"
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build Complete: ./yai"

# Compilazione moduli interni
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilazione cJSON (Speciale)
$(OBJ_DIR)/cJSON.o: $(EXTERNAL_SRC)
	@mkdir -p $(OBJ_DIR)
	@echo "CC (ext) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean