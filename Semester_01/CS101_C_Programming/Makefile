# Compiler Settings
CC = gcc
CFLAGS = -Wall -g

# Folders
SRC_DIR = src
BUILD_DIR = build

# The Target Executable
TARGET = $(BUILD_DIR)/program

# Find all .c files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Default Rule: Build everything
all: $(TARGET)
	@echo "✅ Build Successful! Run with: make run"

# Link
$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

# Run Rule
run: all
	@echo "🚀 Running..."
	@./$(TARGET)

# Clean Rule
clean:
	@rm -rf $(BUILD_DIR)
	@echo "🧹 Cleaned up."