# Project name
PROJECT := bigfib


# Directories
SRC := src
BUILD := build
BIN := bin

# Directories management
MKDIR := mkdir -pv
RM := rm -rfv
CP := cp -ruv


# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic
LIBS =
LDFLAGS =

# Main target
TARGET := $(BIN)/$(PROJECT)

# Targets
.PHONY: release debug clean

release: CXXFLAGS += -O3
release: $(TARGET)

debug: CXXFLAGS += -Og -ggdb3
debug: $(TARGET)

clean:
	$(RM) $(BUILD) $(BIN)


# Directories creation
.PRECIOUS: $(BUILD)/ $(BUILD)%/ $(BIN)/
.SECONDEXPANSION:

$(BUILD)/:
	$(MKDIR) $@

$(BUILD)%/:
	$(MKDIR) $@

$(BIN)/:
	$(MKDIR) $@

# CXX files
CXXSOURCES := $(shell find $(SRC) -type f -name *.cpp)
CXXOBJECTS := $(patsubst $(SRC)/%,$(BUILD)/%,$(CXXSOURCES:.cpp=.o))


# Compilation
$(TARGET): $(CXXOBJECTS) | $$(@D)/
	$(CXX) -o $@ $^ $(LIBS) $(LDFLAGS)

$(BUILD)/%.o: $(SRC)/%.cpp | $$(@D)/
	$(CXX) $(CXXFLAGS) -o $@ -c $<
