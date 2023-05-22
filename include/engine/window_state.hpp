#pragma once

#include "engine/events/event_manager.hpp"
#include "engine/scenes/llscene.hpp"
#include "engine/window.hpp"

namespace ll::engine {

class WindowState : public WindowedObject {
private:
  events::EventManager _eventManager;
  std::shared_ptr<scene::AbstractScene> _currentScene = nullptr;

public:
  explicit WindowState(std::shared_ptr<Window> window)
      : WindowedObject(window), _eventManager(window) {}

  inline events::EventManager& eventManager() { return _eventManager; }

  std::shared_ptr<scene::AbstractScene> currentScene();
  void setScene(std::shared_ptr<scene::AbstractScene> scene);
};

}// namespace ll::engine
