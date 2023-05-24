#include "logic/scenes.hpp"
#include "logic/objects.hpp"

#include "engine/engine.hpp"

#include <string>

namespace ll::logic::scenes {

static std::unordered_map<std::string, std::shared_ptr<s::AbstractScene>> allScenes;

void init(const std::shared_ptr<ll::engine::WindowState>& w) {
  auto mainScene = std::make_shared<MainScene>(w->window());
  mainScene->addObject(objects::MainImguiObject::instance());
  allScenes[mainScene->name()] = mainScene;

  auto scene1 = std::make_shared<Scene1>(w->window());
  scene1->addObject(objects::MainImguiObject::instance());
  auto simpleTriangle = std::make_shared<objects::scene1::SimpleTriangle>();
  auto simpleTriangleImgui = std::make_shared<objects::scene1::SimpleTriangleImgui>(*simpleTriangle);
  scene1->addObject(simpleTriangle);
  scene1->addObject(simpleTriangleImgui);
  allScenes[scene1->name()] = scene1;

  auto scene2 = std::make_shared<Scene2>(w->window());
  scene2->addObject(objects::MainImguiObject::instance());
  auto circle = std::make_shared<objects::scene2::Circle>();
  scene2->addObject(circle);
  allScenes[scene2->name()] = scene2;

  w->setScene(mainScene);
}

void cleanup() {
  allScenes.clear();
}

const std::unordered_map<std::string, std::shared_ptr<s::AbstractScene>>& scenes() {
  return allScenes;
}

}// namespace ll::logic::scenes
