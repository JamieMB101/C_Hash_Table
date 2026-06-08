# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm

# Directories
SRC_DIR = src
BUILD_DIR = Build

# Target executable name
TARGET = $(BUILD_DIR)/spellcheck

# Explicitly list source files instead of using wildcard
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/hash_table.c $(SRC_DIR)/prime.c

# Default rule to compile everything
all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(TARGET)

# Clean rule to wipe compiled binaries
clean:
	rm -rf $(BUILD_DIR)