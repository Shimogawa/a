#include "logic/imgui.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace ll::logic::imgui {

static int fc = 0;

void imguiInit(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
  io.Fonts->AddFontFromFileTTF("./res/Ubuntu.ttf", 18.0f);
}

void updateImguiFrame() {
  ImGui_ImplGlfw_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  fc++;

  // ImGui::ShowDemoWindow(nullptr);
  {
    ImGui::Begin("info");
    auto&& io = ImGui::GetIO();
    ImGui::Text("F# %d, FR %.2f, DT %.2f", fc, io.Framerate, 1000.0f / io.Framerate);
    ImGui::End();
  }

  ImGui::Render();
}

void imguiCleanup() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

}// namespace ll::logic::imgui
