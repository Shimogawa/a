#include "engine/scenes/llscene.hpp"

namespace ll::engine::scene {

AbstractScene::~AbstractScene() = default;

void AbstractScene::update() {
  for (auto& obj: _objects) {
    obj->update();
  }
  for (auto& obj: _objects) {
    obj->render(*_window);
  }
}

void AbstractScene::updateImgui() {
  for (auto& obj: _objects) {
    obj->updateImgui();
  }
  for (auto& obj: _objects) {
    obj->renderImgui(*_window);
  }
}

void AbstractScene::addObject(std::shared_ptr<RenderableObject> obj) {
  _objects.push_back(obj);
}

}// namespace ll::engine::scene
