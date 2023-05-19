#pragma once
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "engine/scenes/llscene.hpp"
#include "engine/shader.hpp"

#include <memory>
#include <string>
#include <utility>

namespace ll::logic::scenes {

namespace s = ll::engine::scene;

std::shared_ptr<s::AbstractScene> getCurrentScene();

void setCurrentScene(std::shared_ptr<s::AbstractScene> s);

class Scene1 : public s::AbstractScene {
private:
  ll::engine::Shader shader;
  GLuint vao;
  GLuint vbo;

  float color[3] = {0.0f};

public:
  Scene1(GLFWwindow* window);
  ~Scene1();
  void drawImgui() override;
  void draw() override;
  std::string name() override;
};

}// namespace ll::logic::scenes
