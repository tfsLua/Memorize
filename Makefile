# ========== CONFIG ========== #
CC = gcc
CFLAGS = -Wall -Iinclude -Ilibs/cli-lib/include

PROJ_NAME = memorize
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)
SRC_DIR = src
LIB_SRC_DIR = libs/cli-lib/src

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES = $(wildcard $(LIB_SRC_DIR)/*.c)
ALL_SRC = $(SRC_FILES) $(LIB_FILES)

OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(ALL_SRC)))

# ========== RULES ========== #
all: $(BIN_DIR)/$(PROJ_NAME)

$(BIN_DIR)/$(PROJ_NAME): $(OBJ_DIR) $(OBJ_FILES)
	@echo Linking...
	@$(CC) $(OBJ_FILES) -o $@
	@echo Build complete: $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $< ...
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_SRC_DIR)/%.c
	@echo Compiling libs $< ...
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo Cleaned.

run: all
	@./$(BIN_DIR)/$(PROJ_NAME)
