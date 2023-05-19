#define GLFW_INCLUDE_NONE
#include "imgui.h"

#include "engine/shader.hpp"
#include "logic/scenes.hpp"

#include <string>

namespace ll::logic::scenes {

Scene1::Scene1(GLFWwindow* window)
    : s::AbstractScene(window),
      shader("res/shaders/scene1/vertex.glsl", "res/shaders/scene1/fragment.glsl") {
  if (shader.fail()) {
    std::cerr << "fail: " << shader.errorMessage() << '\n';
    return;
  }
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,// left
    0.5f, -0.5f, 0.0f, // right
    0.0f, 0.5f, 0.0f   // top
  };

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Scene1::~Scene1() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void Scene1::drawImgui() {
  ImGui::Begin("Scene 1");
  ImGui::SliderFloat3("RGB", color, 0.0f, 1.0f);
  ImGui::End();
}

void Scene1::draw() {
  shader.use();
  shader.setUniform("ourColor", color[0], color[1], color[2], 1.0f);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::string Scene1::name() {
  return "Scene 1";
}

}// namespace ll::logic::scenes
