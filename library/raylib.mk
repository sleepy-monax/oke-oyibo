LIBRARIES+=library/raylib/libraylib.a
INCLUDES+=-Ilibrary/raylib/src/
LDFLAGS+=$(shell pkg-config --cflags --libs x11) -ldl -lpthread -lm

library/raylib/libraylib.a:
	make -C library/raylib/src PLATFORM=PLATFORM_DESKTOP
