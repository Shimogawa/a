#pragma once

#include "GLFW/glfw3.h"

namespace ll::engine {

class EngineObject {
public:
  virtual ~EngineObject() = 0;

protected:
  GLFWwindow* _window;

  explicit EngineObject(GLFWwindow* window) : _window(window) {}

public:
  [[nodiscard]] inline GLFWwindow* window() const { return _window; }
};

inline EngineObject::~EngineObject() {}

}// namespace ll::engine
