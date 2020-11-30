.DEFAULT_GOAL := all

TARGET?=debug

OBJ_DIRECTORY=obj/$(TARGET)
BIN_DIRECTORY=bin/$(TARGET)

PROJECT = oke-oyibo
SOURCES = $(wildcard src/*.cpp) \
		  $(wildcard src/*/*.cpp) \
		  $(wildcard src/*/*/*.cpp) \
		  $(wildcard lib/*.cpp)

OBJECTS = $(patsubst %.cpp, $(OBJ_DIRECTORY)/%.o, $(SOURCES))

GUARD=@mkdir -p $(@D)

LDFLAGS = -lm
CXXFLAGS = \
	-std=c++20 \
	-MD \
	-Wall \
	-Wextra  \
	-Werror \
	-I. \
	-Isrc/ \
	$(INCLUDES) \
	$(DEFINES)

include library/*.mk
include cfg/$(TARGET).mk

$(BIN_DIRECTORY)/$(PROJECT): $(OBJECTS)
	$(GUARD)
	@echo [LD] $@
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

$(OBJ_DIRECTORY)/%.o: %.cpp
	$(GUARD)
	@echo [CXX] $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: all clean test

all: $(LIBRARIES) $(BIN_DIRECTORY)/$(PROJECT)

clean:
	rm -rf $(OBJ_DIRECTORY)
	rm -rf $(BIN_DIRECTORY)

run: $(LIBRARIES) $(BIN_DIRECTORY)/$(PROJECT)
	$(BIN_DIRECTORY)/$(PROJECT)

-include $(OBJECTS:.o=.d)
