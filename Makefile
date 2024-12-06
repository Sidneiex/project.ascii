# # Compiler
# CXX = g++

# # Compiler Flags
# CXXFLAGS = -std=c++17 -Wall $(shell pkg-config --cflags opencv4 Magick++) -I/opt/homebrew/opt/ncurses/include

# # Linker Flags
# LDFLAGS = $(shell pkg-config --libs opencv4 Magick++) -lncurses

# # Directories
# SRC_DIR = src
# BUILD_DIR = build

# # Executable Name
# BIN = ascii_art_generator

# # Source and Object Files
# SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# # Default Target
# all: $(BIN)

# # Linking the Executable
# $(BIN): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# # Compiling Object Files
# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	@mkdir -p $(BUILD_DIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Clean Build Artifacts
# clean:
# 	rm -rf $(BUILD_DIR) $(BIN)

# # Phony Targets
# .PHONY: all clean




# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall $(shell pkg-config --cflags opencv4 Magick++) -I/opt/homebrew/opt/ncurses/include

# Linker Flags
LDFLAGS = $(shell pkg-config --libs opencv4 Magick++) -lncurses

# Directories
SRC_DIR = src
BUILD_DIR = build

# Executable Name
BIN = ascii_art_generator

# Source and Object Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default Target
all: $(BIN)

# Linking the Executable
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compiling Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN)

# Optional convenience targets

# Run the program with a sample input (adjust input file as needed)
run: $(BIN)
	./$(BIN) input.jpg

# Install the binary to /usr/local/bin (requires sudo)
install: $(BIN)
	sudo cp $(BIN) /usr/local/bin/

# Uninstall the binary
uninstall:
	sudo rm -f /usr/local/bin/$(BIN)

# Phony Targets
.PHONY: all clean run install uninstall