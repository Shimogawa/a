#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "engine/object.hpp"
#include "engine/window_state.hpp"

namespace ll::engine {

class Engine : EngineObject {
private:
  std::unordered_map<ObjectId, std::shared_ptr<WindowState>> _windows;
  std::unordered_map<GLFWwindow*, ObjectId> _glfwWindowMap;
  bool _finished = false;

  Engine();

public:
  ~Engine() override;
  Engine(const Engine&) = delete;
  Engine(Engine&&) = delete;

  std::shared_ptr<WindowState> createWindow(glm::ivec2 size, std::string title);
  std::shared_ptr<WindowState> createWindow(
    int width,
    int height,
    const std::string& title,
    std::function<void(std::shared_ptr<WindowState>)> initializer = nullptr,
    GLFWmonitor* monitor = nullptr,
    std::shared_ptr<Window> share = nullptr);

  void startLoop();

  template <typename T>
  requires(std::is_base_of_v<EngineObject, T>)
  T& findObject(ObjectId id);

  std::shared_ptr<WindowState> findWindowByGlfwWindow(GLFWwindow* window);
  std::shared_ptr<WindowState> getWindowState(Window& window);

  static void clearWindowContext();
  static Engine& instance();
};

template <typename T>
requires(std::is_base_of_v<EngineObject, T>)
T& Engine::findObject(ObjectId id) {
  static_assert(sizeof(T) == 0, "cannot get such object type");
}

}// namespace ll::engine
