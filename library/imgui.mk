DEFINES+=-DIMGUI_IMPL_OPENGL_LOADER_CUSTOM='"library/raylib/src/external/glad.h"'

INCLUDES+= \
	-Ilibrary/imgui/ \
	-Ilibrary/imgui/examples \
	-Ilibrary/raylib/src/external/glfw/include

SOURCES+= \
	library/imgui/examples/imgui_impl_glfw.cpp \
	library/imgui/examples/imgui_impl_opengl3.cpp \
	library/imgui/imgui.cpp \
	library/imgui/imgui_draw.cpp \
	library/imgui/imgui_widgets.cpp \
	library/imgui/imgui_demo.cpp

LDFLAGS+=
