# Makefile for the project

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files
SRCS = main.c mdp.c montecarlo.c

# Object files
BUILD_DIR = build
OBJS = $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))

# Header files
HEADERS = mdp.h montecarlo.h

# Target executable
TARGET = $(BUILD_DIR)/my_program

# Default target
all: $(BUILD_DIR) $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
$(BUILD_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean rule
clean:
	rm -rf $(BUILD_DIR)