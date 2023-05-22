// #include <vector>
// #define GLFW_INCLUDE_NONE
// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
//
// #include <memory>
//
// #include "engine/scenes/llscene.hpp"
// #include "logic/imgui.hpp"
// #include "logic/scenes.hpp"
//
// namespace ll::logic::imgui {
//
// static bool showMetrics = true;
//
// static int fc = 0;
//
// std::vector<std::shared_ptr<ll::engine::scene::AbstractScene>> scenes;
//
// void imguiInit(std::shared_ptr<ll::engine::Window> window) {
//   IMGUI_CHECKVERSION();
//   ImGui::CreateContext();
//   ImGuiIO& io = ImGui::GetIO();
//   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
//   io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
//   ImGui::StyleColorsDark();
//   ImGui_ImplGlfw_InitForOpenGL(window->glfwWindow(), true);
//   ImGui_ImplOpenGL3_Init("#version 130");
//   io.Fonts->AddFontFromFileTTF("./res/Ubuntu.ttf", 18.0f);
//
//   scenes = {
//     std::shared_ptr<ll::engine::scene::AbstractScene>(new ll::logic::scenes::Scene1(window)),
//   };
// }
//
// void updateImguiFrame(
//   GLFWwindow* window,
//   std::shared_ptr<ll::engine::scene::AbstractScene> scene) {
//   ImGui_ImplGlfw_NewFrame();
//   ImGui_ImplOpenGL3_NewFrame();
//   ImGui::NewFrame();
//
//   fc++;
//
//   // ImGui::ShowDemoWindow(nullptr);
//   {
//     ImGui::Begin("Info");
//     ImGui::BeginChild("scenes", ImVec2(0, ImGui::GetFrameHeightWithSpacing() + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
//     if (ImGui::Button("Clear scene"))
//       ll::logic::scenes::setCurrentScene(nullptr);
//
//     for (const auto& s: scenes) {
//       ImGui::SameLine();
//       ImGui::PushID(static_cast<int>(s->id()));
//       if (ImGui::Button(s->name().c_str()))
//         ll::logic::scenes::setCurrentScene(s);
//       ImGui::PopID();
//     }
//     // ImGui::SameLine();
//     // if (ImGui::Button("Scene 1"))
//     //   ll::logic::scenes::setCurrentScene(
//     //     std::shared_ptr<ll::engine::scene::AbstractScene>(new ll::logic::scenes::Scene1(window)));
//     ImGui::EndChild();
//     if (ImGui::Button(showMetrics ? "Hide metrics" : "Show metrics")) {
//       showMetrics = !showMetrics;
//     }
//     if (showMetrics) {
//       ImGui::Separator();
//       auto&& io = ImGui::GetIO();
//       ImGui::Text("F# %d, FR %.2f", fc, io.Framerate);
//     }
//     ImGui::End();
//   }
//   if (scene != nullptr)
//     scene->updateImgui();
//
//   ImGui::Render();
// }
//
// void imguiCleanup() {
//   ImGui_ImplOpenGL3_Shutdown();
//   ImGui_ImplGlfw_Shutdown();
//   ImGui::DestroyContext();
//
//   scenes.clear();
// }
//
// }// namespace ll::logic::imgui
