#pragma once

#include <GLFW/glfw3.h>

#include "engine/object.hpp"
namespace ll::engine::events {

enum EventType {
  FRAME_BUFFER_SIZE = 518,
};

class AbstractEvent : public EngineObject {
public:
  virtual ~AbstractEvent() = 0;

protected:
  explicit AbstractEvent(GLFWwindow* window) : EngineObject(window) {}

public:
  [[nodiscard]] virtual EventType type() const = 0;
};

class GLFrameBufferSizeEvent : public AbstractEvent {
private:
  int _width, _height;

public:
  GLFrameBufferSizeEvent(GLFWwindow* window, int width, int height)
      : AbstractEvent(window), _width(width), _height(height) {}
  ~GLFrameBufferSizeEvent() override {}
  [[nodiscard]] EventType type() const override;
  [[nodiscard]] int width() const;
  [[nodiscard]] int height() const;
};

}// namespace ll::engine::events
