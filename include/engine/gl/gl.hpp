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
  bool _hasError = true;
  std::string _message;
  GLObject() = default;

public:
  virtual ~GLObject() = 0;

  [[nodiscard]] inline GLuint id() const { return _id; }
  [[nodiscard]] inline bool valid() { return _id != 0; }

  [[nodiscard]] inline bool ok() const { return !_hasError; }
  [[nodiscard]] inline bool fail() const { return _hasError; }
  [[nodiscard]] inline std::string errorMessage() const { return _message; }
};

class GLUsableObject : public GLObject {
protected:
  GLUsableObject() = default;

public:
  virtual ~GLUsableObject() = 0;

  virtual void use() = 0;
  virtual void use(GLenum) = 0;
};

}// namespace ll::engine::gl
