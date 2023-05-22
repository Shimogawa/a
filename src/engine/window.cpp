#include "engine/window.hpp"

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace ll::engine {

Window::~Window() = default;

std::shared_ptr<Window> Window::newWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, std::shared_ptr<Window> share) {
  auto w = glfwCreateWindow(width, height, title.c_str(), monitor, share == nullptr ? nullptr : share->glfwWindow());
  if (w == nullptr) {
    std::cerr << "unable to create window\n";
    return nullptr;
  }
  glfwMakeContextCurrent(w);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    glfwDestroyWindow(w);
    return nullptr;
  }
  return std::make_shared<Window>(w);
}

bool Window::alive() {
  return _window != nullptr;
}

bool Window::shouldClose() {
  if (!alive())
    return false;
  if (_shouldClose)
    return true;
  _shouldClose = glfwWindowShouldClose(_window);
  return _shouldClose;
}

void Window::destroy() {
  if (!alive()) return;
  glfwDestroyWindow(_window);
  _window = nullptr;
}

void Window::makeCurrentContext() {
  if (!alive()) return;
  glfwMakeContextCurrent(_window);
}

void Window::swapBuffers() {
  if (!alive()) return;
  glfwSwapBuffers(_window);
}

}// namespace ll::engine
