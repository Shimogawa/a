#include "logic/objects.hpp"

#include "engine/gl/shader.hpp"
#include "glad/glad.h"

#include <iostream>

namespace ll::logic::objects::scene2 {

Circle::Circle()
    : _shader(engine::Shader("res/shaders/scene2/fragment.glsl", engine::gl::ShaderType::FRAGMENT),
              engine::Shader("res/shaders/scene2/vertex.glsl", engine::gl::ShaderType::VERTEX)) {
  if (_shader.fail()) {
    std::cerr << "fail: " << _shader.errorMessage() << '\n';
    return;
  }
  float right = 0.5;
  float bottom = -0.5;
  float left = -0.5;
  float top = 0.5;
  float quad[20] = {
    //x, y, z, lx, ly
    right,
    bottom,
    0,
    1.0,
    -1.0,
    right,
    top,
    0,
    1.0,
    1.0,
    left,
    top,
    0,
    -1.0,
    1.0,
    left,
    bottom,
    0,
    -1.0,
    -1.0,
  };
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, quad, GL_STATIC_DRAW);
  glVertexAttribPointer(_shader.getAttribLocation("vertex"), 3, GL_FLOAT, GL_FALSE, 20, nullptr);
  glVertexAttribPointer(_shader.getAttribLocation("value"), 2, GL_FLOAT, GL_FALSE, 20, (char*) nullptr + 12);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Circle::~Circle() {
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
}

void Circle::render(ll::engine::Window& w) {
  _shader.use();
  glm::mat4 projectionM = glm::mat4(1.0);
  projectionM[1][1] = 8.0f / 6;//aspect ratio
  glm::mat4 viewM = glm::mat4(1.0);
  _shader.setUniformMatrix("projectionMatrix", projectionM);
  _shader.setUniformMatrix("viewMatrix", viewM);
  glBindVertexArray(_vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

}// namespace ll::logic::objects::scene2
