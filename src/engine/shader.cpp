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

void Shader::use() {
  if (_hasError)
    return;
  glUseProgram(_programId);
}

Shader::~Shader() {
  if (_hasError)
    return;
  glDeleteProgram(_programId);
}

}// namespace ll::engine
