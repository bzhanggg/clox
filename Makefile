# Root Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Directories
LIB_DIR = lib
SRC_DIR = src

# Object files from lib and src directories
LIB_OBJS = $(wildcard $(LIB_DIR)/*.o)
SRC_OBJS = $(wildcard $(SRC_DIR)/*.o)

# Output executable
TARGET = main

# Default target
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(LIB_OBJS) $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB_OBJS) $(SRC_OBJS)

# Clean up generated files
clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean
	rm -f $(TARGET)

# Build the libraries and main source
$(LIB_OBJS):
	$(MAKE) -C $(LIB_DIR)

$(SRC_OBJS):
	$(MAKE) -C $(SRC_DIR)

# Phony targets
.PHONY: all clean
