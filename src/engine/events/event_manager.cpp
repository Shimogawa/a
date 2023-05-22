#include "engine/events/event_manager.hpp"
#include "engine/engine.hpp"

#include <cassert>

namespace ll::engine::events {

static std::unordered_map<ObjectId, ll::engine::utils::SafeQueue<std::unique_ptr<AbstractEvent>>> eventQueue;

namespace callbacks {

  void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    auto engineWindow = Engine::instance().findWindowByGlfwWindow(window)->window();
    eventQueue[engineWindow->id()]
      .push(std::make_unique<ll::engine::events::GLFrameBufferSizeEvent>(engineWindow, width, height));
  }

}// namespace callbacks

void setupCallbacks(std::shared_ptr<Window>& window) {
  glfwSetFramebufferSizeCallback(window->glfwWindow(), callbacks::frameBufferSizeCallback);
}

EventManager::EventManager(std::shared_ptr<Window> window) : _window(window) {
  if (eventQueue.contains(window->id())) {
    assert(false && "should not initialize more than one event manager on a window");
  }
  eventQueue.insert(std::pair<ObjectId, ll::engine::utils::SafeQueue<std::unique_ptr<AbstractEvent>>>{window->id(), utils::SafeQueue<std::unique_ptr<AbstractEvent>>()});
  setupCallbacks(window);
}

void EventManager::update() {
  if (!_enabled)
    return;
  auto& q = eventQueue[_window->id()];
  while (!q.empty()) {
    auto event = q.dequeue();
    if (!_eventHandlers.contains(event->type()))
      continue;
    event->window()->makeCurrentContext();
    for (auto& h: _eventHandlers[event->type()]) {
      h(event.get());
    }
  }
}

inline void EventManager::enable() {
  _enabled = true;
}

inline void EventManager::disable() {
  _enabled = false;
}

inline bool EventManager::enabled() const {
  return _enabled;
}

}// namespace ll::engine::events
