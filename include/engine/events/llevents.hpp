#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "engine/events/common.hpp"
#include "engine/object.hpp"
#include "engine/utils.hpp"
#include "engine/window.hpp"

namespace ll::engine::events {

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

}// namespace ll::engine::events
