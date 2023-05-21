#pragma once

#include <cstdint>

#include "GLFW/glfw3.h"

namespace ll::engine {

using ObjectId = uint64_t;

class EngineObject {
private:
  ObjectId _id;

public:
  virtual ~EngineObject() = 0;
  EngineObject(const EngineObject& other) = delete;
  EngineObject(EngineObject&& other) = delete;

  virtual void preUpdate() {}
  virtual void update() {}
  virtual void updateImgui() {}
  virtual void postUpdate() {}


  [[nodiscard]] inline ObjectId id() const { return _id; }
  static EngineObject& findObject(ObjectId id);
  bool objectExists(ObjectId id);

protected:
  EngineObject();
};

}// namespace ll::engine
