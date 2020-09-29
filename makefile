.DEFAULT_GOAL := all

PROJECT = oke-oyibo
SOURCES = $(wildcard source/*.cpp) $(wildcard library/*.cpp) $(wildcard source/*/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

LDFLAGS = -lm
CXXFLAGS = -g \
		 -std=c++17 \
		 -MD \
		 -Wall \
		 -Wextra  \
		 -fsanitize=address \
		 -fsanitize=undefined \
		 -I. \
		 -Isource/ \
		 $(INCLUDES) \
		 $(DEFINES) \

include library/*.mk

$(PROJECT).out: $(OBJECTS)
	$(CXX) -fsanitize=address -fsanitize=undefined -o $@ $^ $(LIBRARIES) $(LDFLAGS)

.PHONY: all clean test

all: $(LIBRARIES) $(PROJECT).out

clean:
	rm -f $(OBJECTS) $(SOURCES:.cpp=.d) $(PROJECT).out

debug: $(LIBRARIES) $(PROJECT).out
	./$(PROJECT).out

-include $(SOURCES:.cpp=.d)
