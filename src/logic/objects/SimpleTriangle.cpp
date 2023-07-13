#include "logic/objects.hpp"

#include "glad/glad.h"

#include <iostream>

namespace ll::logic::objects::scene1 {

SimpleTriangle::SimpleTriangle()
    : _shader(
        engine::Shader("res/shaders/scene1/vertex.glsl", engine::gl::ShaderType::VERTEX),
        engine::Shader("res/shaders/scene1/fragment.glsl", engine::gl::ShaderType::FRAGMENT)),
      _texture("res/textures/wall.jpg") {
  if (_shader.fail()) {
    std::cerr << "fail: " << _shader.errorMessage() << '\n';
    return;
  }

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// left
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // right
    0.0f, 0.5f, 0.0f, 0.5f, 1.0f   // top
  };

  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);
  glBindVertexArray(_vao);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const int stride = 3 + 2;

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  _shader.use();
  _shader.setUniform("ourTexture", 0);
}

SimpleTriangle::~SimpleTriangle() {
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
}

void SimpleTriangle::render(ll::engine::Window& w) {
  _texture.use(GL_TEXTURE0);
  _shader.use();
  _shader.setUniform("ourColor", _color.r, _color.g, _color.b, 1.0f);
  glBindVertexArray(_vao);
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (uint32_t[3]){0, 1, 2});
}

}// namespace ll::logic::objects::scene1
