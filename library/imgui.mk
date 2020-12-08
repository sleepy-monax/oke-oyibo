DEFINES+=-DIMGUI_IMPL_OPENGL_LOADER_CUSTOM='"library/raylib/src/external/glad.h"'

INCLUDES+= \
	-Ilibrary/imgui/ \
	-Ilibrary/imgui/examples \
	-Ilibrary/raylib/src/external/glfw/include

SOURCES+= \
	library/imgui/imgui.cpp \
	library/imgui/imgui_draw.cpp \
	library/imgui/imgui_widgets.cpp

LDFLAGS+=
