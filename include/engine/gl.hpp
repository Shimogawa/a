#pragma once

#include <fmt/core.h>
#include <glad/glad.h>

namespace ll::engine::gl {

enum ShaderType {
  VERTEX,
  FRAGMENT,
};

class GLObject {
protected:
  GLuint _id = 0;
  GLObject() = default;

public:
  virtual ~GLObject() = 0;

  [[nodiscard]] inline GLuint id() const { return _id; }
  inline bool valid() { return _id != 0; }
};

}// namespace ll::engine::gl
