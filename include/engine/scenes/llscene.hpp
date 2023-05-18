#pragma once

#include <GLFW/glfw3.h>
#include <stdint.h>
#include <string>

#include "engine/object.hpp"

namespace ll::engine::scene {

class AbstractScene : public EngineObject {
private:
  uint64_t _id;

public:
  virtual ~AbstractScene() = 0;

  virtual std::string name() = 0;

  virtual void drawImgui() = 0;
  virtual void draw() = 0;

  inline uint64_t id() {
    return _id;
  }

protected:
  explicit AbstractScene(GLFWwindow* window);
};

}// namespace ll::engine::scene
