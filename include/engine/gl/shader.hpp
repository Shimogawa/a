#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <type_traits>
#include <vector>

#include "engine/gl/gl.hpp"
#include "engine/utils.hpp"

namespace ll::engine {

class ShaderBase : public gl::GLObject {
protected:
  ShaderBase() = default;
  bool _hasError = true;
  std::string _message;

public:
  virtual ~ShaderBase() = 0;

  [[nodiscard]] inline bool ok() const { return !_hasError; }
  [[nodiscard]] inline bool fail() const { return _hasError; }
  inline std::string errorMessage() { return _message; }
};

class Shader : public ShaderBase {
private:
  gl::ShaderType _type;

public:
  Shader(const std::string& path, gl::ShaderType type);
  ~Shader() override;

  inline gl::ShaderType type() { return _type; }
};

class ShaderProgram : public ShaderBase {
public:
  template <typename... T>
  requires(std::is_same_v<Shader, T> && ...)
  explicit ShaderProgram(T... shaders);
  explicit ShaderProgram(const std::vector<Shader>& shaders);
  ~ShaderProgram() override;

  void use();
  GLint getUniformLocation(const std::string& name);

  template <typename T, typename... Ts>
  void setUniform(const std::string& name, T value, Ts... values);
  template <>
  void setUniform<GLint>(const std::string& name, GLint value);
  template <>
  void setUniform<>(const std::string& name, bool value);
  template <>
  void setUniform<>(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
};

template <typename T, typename... Ts>
void ShaderProgram::setUniform(const std::string&, T, Ts...) {
  static_assert(sizeof(T) == 0, "no such definition");
}

template <typename... T>
requires(std::is_same_v<Shader, T> && ...)
ShaderProgram::ShaderProgram(T... shaders)
    : ShaderProgram(
#ifdef _MSC_VER
        std::vector<Shader>
#endif
        {shaders...}) {
}

}// namespace ll::engine