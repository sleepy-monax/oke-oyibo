library/libraylib.a:
	make -C library/raylib/src PLATFORM=PLATFORM_DESKTOP
	cp library/raylib/libraylib.a library/libraylib.a

LIBRARIES+=library/libraylib.a
