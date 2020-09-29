#include <GLFW/glfw3.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glue/Glue.h"

namespace glue
{
    void initialize()
    {
        const int screenWidth = 800;
        const int screenHeight = 450;

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
        SetTargetFPS(60);

        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow *>(GetWindowGLFWHandle()), true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void begin_frame()
    {
        BeginDrawing();
        ClearBackground(BLUE);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    bool should_exit()
    {
        return WindowShouldClose();
    }

    void end_frame()
    {
        rlglDraw();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        EndDrawing();
    }

    void uninitialize()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        CloseWindow();
    }
} // namespace glue
