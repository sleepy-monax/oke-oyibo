PROJECT = oke-oyibo
SOURCES = $(wildcard source/*.cpp) $(wildcard source/*/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

LDFLAGS = -lraylib -lm
CFLAGS = -g \
		 -std=c++17 \
		 -MD \
		 -Isource \
		 -Wall \
		 -Wextra  \
		 -Werror \
		 -fsanitize=address \
		 -fsanitize=undefined

$(PROJECT).out: $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean test

all: $(PROJECT).out

clean:
	rm -f $(OBJECTS) $(SOURCES:.cpp=.d) $(PROJECT).out

debug: $(PROJECT).out
	./$(PROJECT).out

-include $(SOURCES:.cpp=.d)
