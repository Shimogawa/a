#pragma once

#include <memory>
#include <string>
#include <utility>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "engine/object.hpp"

namespace ll::engine {

class Window : public EngineObject {
private:
  GLFWwindow* _window;
  bool _shouldClose = false;

public:
  explicit Window(GLFWwindow* glfwwindow) : EngineObject(), _window(glfwwindow) {}

  ~Window() override;

  [[nodiscard]] inline GLFWwindow* glfwWindow() const { return _window; }

  bool alive();
  bool shouldClose();
  void destroy();
  void makeCurrentContext();
  void swapBuffers();

  static std::shared_ptr<Window> newWindow(
    int width, int height, const std::string& title, GLFWmonitor* monitor, std::shared_ptr<Window> share);
};

class WindowedObject : public EngineObject {
protected:
  std::shared_ptr<Window> _window;

public:
  explicit WindowedObject(std::shared_ptr<Window> window) : EngineObject(), _window(std::move(window)) {}

  [[nodiscard]] inline std::shared_ptr<Window> window() const { return _window; }
};

}// namespace ll::engine