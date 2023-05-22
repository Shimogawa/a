#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "engine/object.hpp"
#include "engine/utils.hpp"
#include "engine/window.hpp"

namespace ll::engine::scene {

class RenderableObject : public EngineObject {
public:
  virtual void render(Window& w) {}
  virtual void renderImgui(Window& w) {}
};

class AbstractScene : public WindowedObject {
private:
  std::vector<std::shared_ptr<RenderableObject>> _objects;

public:
  virtual ~AbstractScene() = 0;

  virtual std::string name() = 0;

  void update() override;
  void updateImgui() override;

  // template <typename T>
  // requires(std::is_base_of_v<RenderableObject, T>)
  // void addObject(std::shared_ptr<T> obj);
  void addObject(std::shared_ptr<RenderableObject> obj);

protected:
  explicit AbstractScene(std::shared_ptr<Window> window) : WindowedObject(std::move(window)) {}
};

// template <typename T>
// requires(std::is_base_of_v<RenderableObject, T>)
// void AbstractScene::addObject(std::shared_ptr<T> obj) {
//   _objects.push_back(std::static_pointer_cast<RenderableObject>(obj));
// }

}// namespace ll::engine::scene
