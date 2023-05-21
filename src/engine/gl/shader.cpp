#define GLFW_INCLUDE_NONE
#include "engine/gl/shader.hpp"
#include "engine/gl/gl.hpp"
#include "engine/utils.hpp"

#include <fmt/format.h>

#include <algorithm>
#include <iterator>
#include <variant>

namespace ll::engine {

ShaderBase::~ShaderBase() = default;

Shader::Shader(const std::string& path, gl::ShaderType type) : _type(type) {
  auto code = utils::readFullFile(path);
  if (!code) {
    _hasError = true;
    _message = fmt::format("failed to read {} shader {}", fmt::enums::format_as(type), path);
    return;
  }
  auto shader = utils::gl::compileShader(code.value(), type);
  if (std::holds_alternative<std::string>(shader)) {
    _hasError = true;
    _message = fmt::format("failed to compile {} shader:\n{}", fmt::enums::format_as(type), std::get<std::string>(shader));
    return;
  }
  _id = std::get<GLuint>(shader);
}

Shader::~Shader() {
  if (_hasError)
    return;
  glDeleteShader(_id);
}

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders) {
  std::vector<GLuint> ids;
  ids.reserve(shaders.size());
  std::transform(
    shaders.begin(),
    shaders.end(),
    std::back_inserter(ids),
    [](const Shader& s) { return s.id(); });
  auto p = utils::gl::createProgram(ids);
  if (std::holds_alternative<std::string>(p)) {
    _hasError = true;
    _message = fmt::format("failed to create program:\n{}", std::get<std::string>(p));
  } else {
    _hasError = false;
    _id = std::get<GLuint>(p);
  }
}

ShaderProgram::~ShaderProgram() {
  if (_hasError)
    return;
  glDeleteProgram(_id);
}

void ShaderProgram::use() {
  if (_hasError)
    return;
  glUseProgram(_id);
}

GLint ShaderProgram::getUniformLocation(const std::string& name) {
  return glGetUniformLocation(_id, name.c_str());
}

template <>
[[maybe_unused]] void ShaderProgram::setUniform<>(const std::string& name, GLint value) {
  glUniform1i(getUniformLocation(name), value);
}

template <>
[[maybe_unused]] void ShaderProgram::setUniform<>(const std::string& name, bool value) {
  glUniform1i(getUniformLocation(name), static_cast<GLint>(value));
}

template <>
void ShaderProgram::setUniform<>(const std::string& name, GLfloat value) {
  glUniform1f(getUniformLocation(name), value);
}

template <>
[[maybe_unused]] void ShaderProgram::setUniform<>(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  glUniform4f(getUniformLocation(name), x, y, z, w);
}

template <>
[[maybe_unused]] void ShaderProgram::setUniform<glm::vec4>(const std::string& name, glm::vec4 value) {
  glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

}// namespace ll::engine
