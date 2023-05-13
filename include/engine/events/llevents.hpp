#pragma once

#include <GLFW/glfw3.h>

namespace ll::engine::events {

enum EventType {
  FRAME_BUFFER_SIZE = 518,
};

class AbstractEvent {
public:
  virtual ~AbstractEvent() = 0;

protected:
  GLFWwindow* _window;

  explicit AbstractEvent(GLFWwindow* window) : _window(window) {}

public:
  [[nodiscard]] inline GLFWwindow* window() const { return _window; }
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
