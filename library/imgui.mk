DEFINES+=-DIMGUI_IMPL_OPENGL_LOADER_CUSTOM='"library/raylib/src/external/glad.h"'

INCLUDES+= \
	-Ilibrary/imgui/ \
	-Ilibrary/imgui/examples \
	-Ilibrary/raylib/src/external/glfw/include

OBJECTS+= \
	library/imgui/examples/imgui_impl_glfw.o \
	library/imgui/examples/imgui_impl_opengl3.o \
	library/imgui/imgui.o \
	library/imgui/imgui_draw.o \
	library/imgui/imgui_widgets.o \
	library/imgui/imgui_demo.o

LDFLAGS+=
