#include "logic/scenes.hpp"

namespace ll::logic::scenes {

static std::shared_ptr<s::AbstractScene> currentScene = nullptr;

std::shared_ptr<s::AbstractScene> getCurrentScene() {
  return currentScene;
}

void setCurrentScene(std::shared_ptr<s::AbstractScene> s) {
  currentScene = std::move(s);
}

}// namespace ll::logic::scenes
