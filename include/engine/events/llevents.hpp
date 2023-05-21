#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "engine/object.hpp"
#include "engine/utils.hpp"
#include "engine/window.hpp"

namespace ll::engine::events {

enum EventType {
  FRAME_BUFFER_SIZE = 518,
};

class AbstractEvent : public WindowedObject {
public:
  virtual ~AbstractEvent() = 0;

protected:
  explicit AbstractEvent(std::shared_ptr<Window> window) : WindowedObject(std::move(window)) {}

public:
  [[nodiscard]] virtual EventType type() const = 0;
};

class GLFrameBufferSizeEvent : public AbstractEvent {
private:
  int _width, _height;

public:
  GLFrameBufferSizeEvent(std::shared_ptr<Window> window, int width, int height)
      : AbstractEvent(std::move(window)), _width(width), _height(height) {}
  ~GLFrameBufferSizeEvent() override = default;
  [[nodiscard]] EventType type() const override;
  [[nodiscard]] int width() const;
  [[nodiscard]] int height() const;
};

class EventManager : public WindowedObject {
public:
  template <typename T>
  using EventHandler = std::function<void(std::unique_ptr<T>)>;

  explicit EventManager(std::shared_ptr<Window> window);

  template <typename T>
  void addHandler(EventType type, EventHandler<T>&& handler)
  requires(std::is_assignable_v<AbstractEvent, T>);

  void enable();
  void disable();
  [[nodiscard]] bool enabled() const;
  void update() override;

private:
  bool _enabled = false;
  std::unordered_map<EventType, std::vector<EventHandler<AbstractEvent>>> _eventHandlers;
};

template <typename T>
void EventManager::addHandler(EventType type, EventHandler<T>&& handler)
requires(std::is_assignable_v<AbstractEvent, T>)
{
  if (!_eventHandlers.contains(type)) {
    _eventHandlers[type] = {std::forward<EventHandler<T>>(handler)};
    return;
  }
  _eventHandlers[type].push_back(std::forward<EventHandler<T>>(handler));
}

}// namespace ll::engine::events
