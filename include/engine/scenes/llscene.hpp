#pragma once

#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "engine/object.hpp"
#include "engine/window.hpp"

namespace ll::engine::scene {

class AbstractScene : public WindowedObject {
private:
  std::vector<std::shared_ptr<EngineObject>> _objects;

public:
  virtual ~AbstractScene() = 0;

  virtual std::string name() = 0;

  void addObject(const std::shared_ptr<EngineObject>& o);

protected:
  explicit AbstractScene(std::shared_ptr<Window> window) : WindowedObject(std::move(window)) {}
};

}// namespace ll::engine::scene
