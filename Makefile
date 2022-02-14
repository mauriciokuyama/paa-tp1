CC := gcc
BIN_NAME := main
BUILD_DIR := build
SRC_DIR := src
OBJ_DIR := $(BUILD_DIR)/.build
BIN_PATH := $(BUILD_DIR)/$(BIN_NAME)
WFLAGS := -Wall \
		  -pedantic
CFLAGS := $(WFLAGS) \
		  -std=c99 \
		  -O2 \
		  -g3
LDFLAGS :=
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

.PHONY: all
all: $(BIN_PATH)

$(BIN_PATH): $(BUILD_DIR) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: run
run: $(BIN_PATH)
	@./$<

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
