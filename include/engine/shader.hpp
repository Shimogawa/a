#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <string>

namespace ll::engine {

class Shader {
private:
  GLuint _programId = 0;
  bool _hasError = true;
  std::string _message;

public:
  Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
  ~Shader();

  inline bool ok() { return !_hasError; }
  inline bool fail() { return _hasError; }
  inline std::string errorMessage() { return _message; }

  void use();
  GLint getUniformLocation(const std::string& name);

  template <int N = 1, typename T>
  void setUniform(const std::string& name, T value);
};

}// namespace ll::engine
