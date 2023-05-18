#pragma once

#include <GLFW/glfw3.h>

#include "engine/object.hpp"

namespace ll::engine::scene {

class AbstractScene : public EngineObject {
public:
  virtual ~AbstractScene() = 0;

  virtual void drawImgui() = 0;
  virtual void draw() = 0;

protected:
  explicit AbstractScene(GLFWwindow* window) : EngineObject(window) {}
};

}// namespace ll::engine::scene
