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
	-std=c++17 \
	-MD \
	-Wall \
	-Wextra  \
	-Werror \
	-I. \
	-Isrc/ \
	-fsanitize=undefined \
	-fsanitize=address \
	$(INCLUDES) \
	$(DEFINES) \

include library/*.mk
include cfg/$(TARGET).mk

$(BIN_DIRECTORY)/$(PROJECT).out: $(OBJECTS)
	$(GUARD)
	@echo [LD] $@
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

$(OBJ_DIRECTORY)/%.o: %.cpp
	$(GUARD)
	@echo [CXX] $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: all clean test

all: $(LIBRARIES) $(BIN_DIRECTORY)/$(PROJECT).out

clean:
	rm -rf $(OBJ_DIRECTORY)
	rm -rf $(BIN_DIRECTORY)

run: $(LIBRARIES) $(BIN_DIRECTORY)/$(PROJECT).out
	$(BIN_DIRECTORY)/$(PROJECT).out

-include $(OBJECTS:.o=.d)
