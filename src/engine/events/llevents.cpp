#include "engine/events/llevents.h"

namespace ll::engine::events {

AbstractEvent::~AbstractEvent() {}

EventType GLSetFrameBufferSizeEvent::type() const {
  return SET_FRAME_BUFFER_SIZE;
}

int GLSetFrameBufferSizeEvent::width() const {
  return _width;
}

int GLSetFrameBufferSizeEvent::height() const {
  return _height;
}

}// namespace ll::engine::events
