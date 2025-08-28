# Variables
USE_ASAN = false;

# Compiler
CXX := ccache g++
CXXFLAGS := -Wall -Werror -Wextra -std=c++17 -fuse-ld=lld -g

ifneq ($(USE_ASAN), false)
    CXXFLAGS += -fsanitize=address
endif

# Directories
SRC_DIR := src
EXCLUDE_DIR = src/old
BIN_DIR := bin
OBJ_DIR := obj

# Find all .cpp files recursively in SRC_DIR (handles nested directories)
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp' -not -path "$(EXCLUDE_DIR)/*")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Output binary
TARGET := $(BIN_DIR)/app

# Detect OS (Windows needs ws2_32)
OS := $(shell uname -s)

BULLET_INC := -I/usr/include/bullet
BULLET_LIB := -L/usr/lib -lBulletDynamics -lBulletCollision -lLinearMath -lspdlog -lfmt

# Linker and include flags
LDFLAGS := -lpthread -lmysqlcppconn $(BULLET_LIB)
INCLUDEFLAGS := -Iinclude $(BULLET_INC)
# ifeq ($(OS), Windows_NT)
# else
#     LDFLAGS :=
# endif

# Default build target
all: $(TARGET)

# Link object files to create the final binary
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $^ -o $@ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) ${LDFLAGS} -c $< -o $@

# Create necessary directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Run the compiled binary
run: all
	./$(TARGET) --host 0.0.0.0 --port 4999