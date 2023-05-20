#pragma once

#include "engine/gl.hpp"
#include "engine/utils.hpp"

#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <optional>
#include <sstream>
#include <string>
#include <variant>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ll::engine::utils {

inline std::optional<std::string> readFullFile(const std::string& path) {
  std::ifstream f(path);
  if (!f) {
    return {};
  }
  std::stringstream buffer;
  buffer << f.rdbuf();
  return buffer.str();
}

inline constexpr bool sizeIs(std::initializer_list<float> ll, size_t s) {
  return ll.size() == s;
}

namespace gl {

  enum IdType {
    SHADER,
    PROGRAM,
  };

  inline std::optional<std::string> isSuccessfulOrLog(GLuint id, IdType idType) {
    GLint success;
    if (idType == IdType::SHADER)
      glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    else
      glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
      GLsizei len;
      if (idType == IdType::SHADER)
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
      else
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
      if (len == 0) return "";
      std::string log(len, 0);
      if (idType == IdType::SHADER)
        glGetShaderInfoLog(id, len, nullptr, log.data());
      else
        glGetProgramInfoLog(id, len, nullptr, log.data());
      return std::string(log);
    }
    return {};
  }

  inline std::variant<GLuint, std::string> compileShader(const std::string& code, ll::engine::gl::ShaderType shaderType) {
    GLuint id = glCreateShader(shaderType == ll::engine::gl::ShaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    auto codeCstr = code.c_str();
    glShaderSource(id, 1, &codeCstr, NULL);
    glCompileShader(id);

    auto successOrLog = isSuccessfulOrLog(id, IdType::SHADER);
    if (successOrLog.has_value()) {
      return successOrLog.value();
    }
    return id;
  }

  inline std::variant<GLuint, std::string> createProgram(const std::vector<GLuint>& shaders) {
    GLuint id = glCreateProgram();
    for (auto& sId: shaders) {
      glAttachShader(id, sId);
    }
    glLinkProgram(id);

    auto successOrLog = isSuccessfulOrLog(id, IdType::PROGRAM);
    if (successOrLog.has_value()) {
      return successOrLog.value();
    }
    return id;
  }

}// namespace gl

}// namespace ll::engine::utils
