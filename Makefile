# Makefile for Dijkstra's Algorithm Project
# 
# A well-structured Makefile for C projects
# Demonstrates professional build practices
#
# Usage:
#   make          - Build the project (release mode)
#   make debug    - Build with debug symbols and no optimization
#   make clean    - Remove all build artifacts
#   make run      - Build and run the program
#   make help     - Show this help message

# Compiler settings
CC = gcc

# Warning flags (catch common mistakes)
WARNINGS = -Wall -Wextra -Werror -Wpedantic

# C standard (C99 for portability)
STANDARD = -std=c99

# Base flags (always used)
CFLAGS = $(WARNINGS) $(STANDARD)

# Release flags (optimization)
RELEASE_FLAGS = -O2 -DNDEBUG

# Debug flags (debugging symbols, no optimization)
DEBUG_FLAGS = -g -O0 -DDEBUG

# Source files
SOURCES = main.c graph.c dijkstra.c

# Object files (replace .c with .o)
OBJECTS = $(SOURCES:.c=.o)

# Header files
HEADERS = dijkstra.h

# Target executable name
TARGET = dijkstra

# Default target: release build
all: CFLAGS += $(RELEASE_FLAGS)
all: $(TARGET)
	@echo "Build complete: $(TARGET)"

# Debug build target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)
	@echo "Debug build complete: $(TARGET)"

# Link object files into executable
$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
# $< = first prerequisite (the .c file)
# $@ = target (the .o file)
%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Build and run
run: all
	@echo ""
	@echo "Running $(TARGET)..."
	@echo "════════════════════════════════════════════════════════════"
	@./$(TARGET)

# Clean build artifacts
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete"

# Help message
help:
	@echo "Dijkstra's Algorithm - Build System"
	@echo ""
	@echo "Targets:"
	@echo "  make          Build the project (release mode)"
	@echo "  make debug    Build with debug symbols"
	@echo "  make clean    Remove all build artifacts"
	@echo "  make run      Build and run the program"
	@echo "  make help     Show this help message"
	@echo ""
	@echo "Files:"
	@echo "  Sources: $(SOURCES)"
	@echo "  Headers: $(HEADERS)"
	@echo "  Output:  $(TARGET)"

# Declare phony targets (not actual files)
.PHONY: all debug clean run help
