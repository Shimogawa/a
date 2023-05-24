#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include "glad/glad.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "engine/engine.hpp"
// #include "logic/events.hpp"
#include "logic/imgui.hpp"
#include "logic/scenes.hpp"

#include <GLFW/glfw3.h>
#include <thread>

// std::shared_ptr<ll::engine::WindowState> initMainWindow() {
//   //   glfwInit();
//   //   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   //   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   //   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//   // #ifdef __APPLE__
//   //   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//   // #endif
//
//   // GLFWwindow* window = glfwCreateWindow(800, 600, "x", nullptr, nullptr);
//   // if (window == nullptr) {
//   //   std::cerr << "no window\n";
//   //   return nullptr;
//   // }
//   auto ws = ll::engine::Engine::instance().createWindow(800, 600, "x", [](ll::engine::Window& w) {
//     ImGuiIO& io = ImGui::GetIO();
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
//     io.Fonts->AddFontFromFileTTF("./res/Ubuntu.ttf", 18.0f);
//     ImGui::StyleColorsDark();
//   });
//
//   // glfwMakeContextCurrent(window);
//   // if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
//   //   std::cout << "Failed to initialize GLAD" << std::endl;
//   //   return nullptr;
//   // }
//
//   // glViewport(0, 0, 800, 600);
//   // ll::logic::events::setupCallbacks(window);
//   // ll::logic::imgui::imguiInit(ws->window());
//   return ws;
// }

// void cleanUp(GLFWwindow* window) {
//   ll::logic::imgui::imguiCleanup();
//   glfwDestroyWindow(window);
//   glfwTerminate();
// }

// void renderLoop(GLFWwindow* window) {
//   std::thread t(
//     [window]() {
//       // glfwMakeContextCurrent(window);
//       while (!glfwWindowShouldClose(window)) {
//         glfwMakeContextCurrent(window);
//         glClear(GL_COLOR_BUFFER_BIT);
//
//         auto scene = ll::logic::scenes::getCurrentScene();
//         if (scene != nullptr) {
//           scene->update();
//         }
//
//         glfwMakeContextCurrent(nullptr);
//         // ll::logic::events::processEvents();
//         glfwMakeContextCurrent(window);
//         ll::logic::imgui::updateImguiFrame(window, scene);
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//         glfwSwapBuffers(window);
//       }
//     });
//
//   glfwMakeContextCurrent(nullptr);
//   while (!glfwWindowShouldClose(window)) {
//     glfwPollEvents();
//   }
//
//   t.join();
// }

int main() {

  // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // auto ws = initMainWindow();
  auto ws = ll::engine::Engine::instance().createWindow(800, 600, "x", [](auto w) {
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.Fonts->AddFontFromFileTTF("./res/Ubuntu.ttf", 18.0f);
    ImFontConfig config;
    config.MergeMode = true;
    io.Fonts->AddFontFromFileTTF("./res/NotoSansSC-Regular.otf", 22.0f, &config, io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->Build();

    ImGui::StyleColorsDark();

    ll::logic::scenes::init(w);
  });
  if (!ws) {
    return 1;
  }

  ws->eventManager().addHandler<ll::engine::events::GLFrameBufferSizeEvent>(
    ll::engine::events::EventType::FRAME_BUFFER_SIZE,
    [](const auto& e) {
      glViewport(0, 0, e.width(), e.height());
    });

  ll::engine::Engine::instance().startLoop();

  ll::engine::Engine::instance().addShutdownHook([]() {
    ll::logic::scenes::cleanup();
  });

  // renderLoop(ws->window()->glfwWindow());
  //
  // cleanUp(ws->window()->glfwWindow());
  return 0;
}
