#include "engine/scenes/llscene.hpp"

namespace ll::engine::scene {

AbstractScene::~AbstractScene() = default;

void AbstractScene::addObject(const std::shared_ptr<EngineObject>& o) {
  _objects.push_back(o);
}

}// namespace ll::engine::scene
