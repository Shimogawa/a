#include "engine/window_state.hpp"

namespace ll::engine {

inline std::shared_ptr<scene::AbstractScene> WindowState::currentScene() {
  return _currentScene;
}

void WindowState::setScene(std::shared_ptr<scene::AbstractScene> scene) {
  if (scene == nullptr) {
    _currentScene = nullptr;
    return;
  }
  if (_currentScene && scene->id() == _currentScene->id()) return;
  _currentScene = std::move(scene);
}

}// namespace ll::engine
