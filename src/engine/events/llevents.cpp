#include "engine/events/llevents.hpp"

namespace ll::engine::events {

AbstractEvent::~AbstractEvent() {}

EventType GLFrameBufferSizeEvent::type() const {
  return SET_FRAME_BUFFER_SIZE;
}

int GLFrameBufferSizeEvent::width() const {
  return _width;
}

int GLFrameBufferSizeEvent::height() const {
  return _height;
}

}// namespace ll::engine::events
