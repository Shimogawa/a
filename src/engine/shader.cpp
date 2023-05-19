#include <initializer_list>
#define GLFW_INCLUDE_NONE
#include "engine/shader.hpp"
#include "engine/utils.hpp"

#include <format>
#include <variant>

namespace ll::engine {

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  auto vShaderCode = utils::readFullFile(vertexShaderPath);
  if (!vShaderCode) {
    _hasError = true;
    _message = std::format("failed to read vertex shader {}", vertexShaderPath);
    return;
  }
  auto fShaderCode = utils::readFullFile(fragmentShaderPath);
  if (!fShaderCode) {
    _hasError = true;
    _message = std::format("failed to read fragment shader {}", fragmentShaderPath);
    return;
  }
  auto v = utils::gl::compileShader(vShaderCode.value(), utils::gl::ShaderType::VERTEX);
  if (std::holds_alternative<std::string>(v)) {
    _hasError = true;
    _message = std::format("failed to compile vertex shader:\n{}", std::get<std::string>(v));
    return;
  }
  auto vId = std::get<GLuint>(v);
  auto f = utils::gl::compileShader(fShaderCode.value(), utils::gl::ShaderType::FRAGMENT);
  if (std::holds_alternative<std::string>(f)) {
    _hasError = true;
    _message = std::format("failed to compile fragment shader:\n{}", std::get<std::string>(f));
    glDeleteShader(vId);
    return;
  }
  auto fId = std::get<GLuint>(f);

  auto p = utils::gl::createProgram({vId, fId});
  if (std::holds_alternative<std::string>(p)) {
    _hasError = true;
    _message = std::format("failed to create program:\n{}", std::get<std::string>(p));
  } else {
    _hasError = false;
    _programId = std::get<GLuint>(p);
  }

  glDeleteShader(vId);
  glDeleteShader(fId);
}

Shader::~Shader() {
  if (_hasError)
    return;
  glDeleteProgram(_programId);
}

void Shader::use() {
  if (_hasError)
    return;
  glUseProgram(_programId);
}

GLint Shader::getUniformLocation(const std::string& name) {
  return glGetUniformLocation(_programId, name.c_str());
}

template <>
void Shader::setUniform<GLint>(const std::string& name, GLint i) {
  glUniform1i(getUniformLocation(name), i);
}

template <>
void Shader::setUniform<bool>(const std::string& name, bool b) {
  glUniform1i(getUniformLocation(name), static_cast<GLint>(b));
}

template <>
void Shader::setUniform<GLfloat>(const std::string& name, GLfloat f) {
  glUniform1f(getUniformLocation(name), f);
}

template <>
void Shader::setUniform<GLfloat>(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  glUniform4f(getUniformLocation(name), x, y, z, w);
}

}// namespace ll::engine
