#include "engine/engine.hpp"

#define GLFW_INCLUDE_NONE
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>

namespace ll::engine {

void imguiInit(Window& window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window.glfwWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void imguiDestroy() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

Engine::Engine() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

Engine& Engine::instance() {
  static Engine _engine;
  return _engine;
}

inline std::shared_ptr<WindowState> Engine::createWindow(glm::ivec2 size, std::string title) {
  return createWindow(size.x, size.y, title);
}

std::shared_ptr<WindowState> Engine::createWindow(
  int width,
  int height,
  const std::string& title,
  std::function<void(std::shared_ptr<WindowState>)> initializer,
  GLFWmonitor* monitor,
  std::shared_ptr<Window> share) {
  auto w = Window::newWindow(width, height, title, monitor, share);
  if (!w) {
    std::cerr << "Unable to create window\n";
    return nullptr;
  }
  auto ws = std::make_shared<WindowState>(w);
  _windows.insert(std::pair(w->id(), ws));
  _glfwWindowMap.insert(std::pair(w->glfwWindow(), w->id()));
  glfwMakeContextCurrent(w->glfwWindow());

  imguiInit(*ws->window());
  initializer(ws);
  return ws;
}

void Engine::startLoop() {
  std::thread t(
    [this]() {
      // glfwMakeContextCurrent(window);
      while (true) {
        for (auto it = _windows.begin(); it != _windows.end();) {
          if (it->second->window()->shouldClose()) {
            it->second->window()->makeCurrentContext();
            imguiDestroy();
            clearWindowContext();
            it->second->window()->destroy();
            it = _windows.erase(it);
          } else if (!it->second->window()->alive()) {
            it = _windows.erase(it);
          } else {
            it++;
          }
        }
        if (_windows.empty()) {
          break;
        }
        for (auto& p: _windows) {
          p.second->window()->makeCurrentContext();
          if (p.second->currentScene())
            p.second->currentScene()->preUpdate();
        }
        for (auto& p: _windows) {
          p.second->window()->makeCurrentContext();
          glClear(GL_COLOR_BUFFER_BIT);
          if (p.second->currentScene())
            p.second->currentScene()->update();
        }
        for (auto& p: _windows) {
          p.second->eventManager().update();
        }
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        for (auto& p: _windows) {
          p.second->window()->makeCurrentContext();
          if (p.second->currentScene())
            p.second->currentScene()->updateImgui();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        for (auto& p: _windows) {
          p.second->window()->swapBuffers();
        }
        for (auto& p: _windows) {
          p.second->window()->makeCurrentContext();
          if (p.second->currentScene())
            p.second->currentScene()->postUpdate();
        }
        // glfwMakeContextCurrent(window);
        // glClear(GL_COLOR_BUFFER_BIT);
        //
        // auto scene = ll::logic::scenes::getCurrentScene();
        // if (scene != nullptr) {
        //   scene->update();
        // }
        //
        // glfwMakeContextCurrent(nullptr);
        // ll::logic::events::processEvents();
        // glfwMakeContextCurrent(window);
        // ll::logic::imgui::updateImguiFrame(window, scene);
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // glfwSwapBuffers(window);
      }
      _finished = true;
    });

  clearWindowContext();
  while (!_finished) {
    glfwPollEvents();
  }

  t.join();
}

template <>
WindowState& Engine::findObject(ObjectId id) {
  return *_windows.at(id);
}

template <>
Window& Engine::findObject(ObjectId id) {
  auto& ws = findObject<WindowState>(id);
  return *ws.window();
}

std::shared_ptr<WindowState> Engine::findWindowByGlfwWindow(GLFWwindow* window) {
  if (!_glfwWindowMap.contains(window))
    return nullptr;
  return _windows.at(_glfwWindowMap.at(window));
}

std::shared_ptr<WindowState> Engine::getWindowState(Window& window) {
  return findWindowByGlfwWindow(window.glfwWindow());
}

std::shared_ptr<scene::AbstractScene> Engine::getCurrentScene(ll::engine::Window& window) {
  return getWindowState(window)->currentScene();
}

void Engine::addShutdownHook(ShutdownHookFunc* func) {
  _shutdownHooks.push_back(func);
}

void Engine::clearWindowContext() {
  glfwMakeContextCurrent(nullptr);
}

Engine::~Engine() {
  _windows.clear();
  _glfwWindowMap.clear();
  for (auto& f: _shutdownHooks) {
    f();
  }
  glfwTerminate();
}

}// namespace ll::engine
