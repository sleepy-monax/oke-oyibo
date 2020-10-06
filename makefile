.DEFAULT_GOAL := all

TARGET?=debug

BUILD_DIRCETORY=build/$(TARGET)

PROJECT = oke-oyibo
SOURCES = $(wildcard source/*.cpp) \
		  $(wildcard source/*/*.cpp) \
		  $(wildcard source/*/*/*.cpp) \
		  $(wildcard library/*.cpp)

OBJECTS = $(patsubst %.cpp, $(BUILD_DIRCETORY)/%.o, $(SOURCES))

GUARD=@mkdir -p $(@D)

LDFLAGS = -lm
CXXFLAGS = \
	-std=c++17 \
	-MD \
	-Wall \
	-Wextra  \
	-Werror \
	-I. \
	-Isource/ \
	$(INCLUDES) \
	$(DEFINES) \

include library/*.mk
include config/$(TARGET).mk

$(BUILD_DIRCETORY)/$(PROJECT).out: $(OBJECTS)
	$(GUARD)
	@echo [LD] $@
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

$(BUILD_DIRCETORY)/%.o: %.cpp
	$(GUARD)
	@echo [CXX] $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: all clean test

all: $(LIBRARIES) $(BUILD_DIRCETORY)/$(PROJECT).out

clean:
	rm -f $(OBJECTS) $(SOURCES:.cpp=.d) $(BUILD_DIRCETORY)/$(PROJECT).out

run: $(LIBRARIES) $(BUILD_DIRCETORY)/$(PROJECT).out
	$(BUILD_DIRCETORY)/$(PROJECT).out

-include $(OBJECTS:.o=.d)
