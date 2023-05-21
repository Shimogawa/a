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

std::shared_ptr<ll::engine::WindowState> initMainWindow() {
  //   glfwInit();
  //   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  //   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // #ifdef __APPLE__
  //   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // #endif

  // GLFWwindow* window = glfwCreateWindow(800, 600, "x", nullptr, nullptr);
  // if (window == nullptr) {
  //   std::cerr << "no window\n";
  //   return nullptr;
  // }
  auto ws = ll::engine::Engine::instance().createWindow(800, 600, "x");

  // glfwMakeContextCurrent(window);
  // if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
  //   std::cout << "Failed to initialize GLAD" << std::endl;
  //   return nullptr;
  // }

  // glViewport(0, 0, 800, 600);
  // ll::logic::events::setupCallbacks(window);
  ll::logic::imgui::imguiInit(ws->window());
  return ws;
}

void cleanUp(GLFWwindow* window) {
  ll::logic::imgui::imguiCleanup();
  glfwDestroyWindow(window);
  glfwTerminate();
}

void renderLoop(GLFWwindow* window) {
  std::thread t(
    [window]() {
      // glfwMakeContextCurrent(window);
      while (!glfwWindowShouldClose(window)) {
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);

        auto scene = ll::logic::scenes::getCurrentScene();
        if (scene != nullptr) {
          scene->update();
        }

        glfwMakeContextCurrent(nullptr);
        // ll::logic::events::processEvents();
        glfwMakeContextCurrent(window);
        ll::logic::imgui::updateImguiFrame(window, scene);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
      }
    });

  glfwMakeContextCurrent(nullptr);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  t.join();
}

int main() {

  // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  auto ws = initMainWindow();
  if (!ws) {
    return 1;
  }

  renderLoop(ws->window()->glfwWindow());

  cleanUp(ws->window()->glfwWindow());
  return 0;
}
