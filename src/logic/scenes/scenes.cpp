#include "logic/scenes.hpp"
#include "logic/objects.hpp"

#include "engine/engine.hpp"

namespace ll::logic::scenes {

static std::vector<std::shared_ptr<s::AbstractScene>> allScenes;

void init(std::shared_ptr<ll::engine::WindowState> w) {
  auto scene1 = std::make_shared<Scene1>(w->window());
  scene1->addObject(objects::MainImguiObject::instance());
  allScenes.push_back(scene1);

  w->setScene(scene1);
}

const std::vector<std::shared_ptr<s::AbstractScene>>& scenes() {
  return allScenes;
}

}// namespace ll::logic::scenes
