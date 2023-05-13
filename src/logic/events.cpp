#define GLFW_INCLUDE_NONE
#define GLFW_NATIVE_INCLUDE_NONE

#include "engine/events/llevents.hpp"
#include "glad/glad.h"

#include "logic/events.hpp"
#include "utils/ptr.hpp"
#include "utils/safeq.hpp"
#include <memory>

namespace ll::logic::events {

namespace lle = ll::engine::events;

static ll::utils::safeq::SafeQueue<std::unique_ptr<lle::AbstractEvent>> eventQ;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  eventQ.push(std::make_unique<ll::engine::events::GLFrameBufferSizeEvent>(window, width, height));
}

void processFrameBufferSizeEvent(std::unique_ptr<lle::GLFrameBufferSizeEvent> event) {
  glfwMakeContextCurrent(event->window());
  glViewport(0, 0, event->width(), event->height());
}

void setupCallbacks(GLFWwindow* window) {
  glfwSetFramebufferSizeCallback(window, ll::logic::events::frameBufferSizeCallback);
}

void processSingleEvent(std::unique_ptr<lle::AbstractEvent>& event) {
  switch (event->type()) {
    case lle::EventType::FRAME_BUFFER_SIZE:
      // processFrameBufferSizeEvent(
      //   std::unique_ptr<lle::GLFrameBufferSizeEvent>(
      //     static_cast<lle::GLFrameBufferSizeEvent*>(event.release())));
      processFrameBufferSizeEvent(ll::utils::ptr::uniquePtrBaseToDerived<lle::GLFrameBufferSizeEvent>(event));
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

}// namespace ll::logic::events
