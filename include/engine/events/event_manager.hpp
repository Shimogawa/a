#pragma once
#include "engine/events/event_manager.hpp"

#include <functional>
#include <memory>

#include "engine/events/common.hpp"
#include "engine/events/llevents.hpp"
#include "engine/window.hpp"

namespace ll::engine::events {

template <typename T>
using EventHandler = std::function<void(T)>;

class EventManager : public EngineObject {
private:
  std::shared_ptr<Window> _window;

public:
  explicit EventManager(std::shared_ptr<Window> window);

  // template <typename T>
  // void addHandler(EventType type, EventHandler<T> handler)
  // requires(std::is_base_of_v<AbstractEvent, T>);
  template <typename E, typename F>
  void addHandler(EventType type, F handler);

  void enable();
  void disable();
  [[nodiscard]] bool enabled() const;
  void update() override;

  inline std::shared_ptr<Window> window() { return _window; }

private:
  bool _enabled = false;
  std::unordered_map<EventType, std::vector<EventHandler<AbstractEvent*>>> _eventHandlers;
};

template <typename E, typename F>
void EventManager::addHandler(EventType type, F handler) {
  auto h = EventHandler<AbstractEvent*>{
    [handler](AbstractEvent* event) {
      E* e = dynamic_cast<E*>(event);
      if (!e) return;
      handler(*e);
    }};
  if (!_eventHandlers.contains(type)) {
    _eventHandlers[type] = {h};
    return;
  }
  _eventHandlers[type].push_back(h);
}

}// namespace ll::engine::events
