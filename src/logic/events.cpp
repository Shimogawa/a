#include "glad/glad.h"

#include "logic/events.hpp"
#include "utils/safeq.hpp"
#include <memory>

namespace lle = ll::engine::events;

static ll::safeq::SafeQueue<std::unique_ptr<lle::AbstractEvent>> eventQ;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  eventQ.push(std::make_unique<ll::engine::events::GLFrameBufferSizeEvent>(window, width, height));
}

void processFrameBufferSizeEvent(std::unique_ptr<lle::GLFrameBufferSizeEvent> event) {
  glfwMakeContextCurrent(event->window());
  glViewport(0, 0, event->width(), event->height());
}

void processSingleEvent(std::unique_ptr<lle::AbstractEvent>& event) {
  switch (event->type()) {
    case ll::engine::events::EventType::SET_FRAME_BUFFER_SIZE:
      processFrameBufferSizeEvent(std::unique_ptr<lle::GLFrameBufferSizeEvent>(static_cast<lle::GLFrameBufferSizeEvent*>(event.release())));
      break;
    default:
      break;
  }
}

void processEvents() {
  while (!eventQ.empty()) {
    auto event = eventQ.dequeue();
    processSingleEvent(event);
  }
}
