TARGET := bulb

BUILD_DIR := ./build

SRCS := $(shell find . -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CFLAGS := -std=c89 -Wall -pedantic -O3

default: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
