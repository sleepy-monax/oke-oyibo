PROJECT = oke-oyibo
SOURCES = $(wildcard source/*.cpp) $(wildcard source/*/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

include library/*.mk

LDFLAGS = $(LIBRARIES) -lpthread $(shell pkg-config --cflags --libs x11) -ldl -lm
CXXFLAGS = -g \
		 -Isource/ \
		 -Ilibrary/ \
		 -std=c++17 \
		 -MD \
		 -Wall \
		 -Wextra  \
		 -Werror \
		 -fsanitize=address \
		 -fsanitize=undefined

$(PROJECT).out: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean test

all: $(LIBRARIES) $(PROJECT).out

clean:
	rm -f $(OBJECTS) $(SOURCES:.cpp=.d) $(PROJECT).out

debug: $(LIBRARIES) $(PROJECT).out
	./$(PROJECT).out

-include $(SOURCES:.cpp=.d)
