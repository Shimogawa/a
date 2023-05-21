#pragma once
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "engine/gl/shader.hpp"
#include "engine/scenes/llscene.hpp"

#include <memory>
#include <string>
#include <utility>

namespace ll::logic::scenes {

namespace s = ll::engine::scene;

std::shared_ptr<s::AbstractScene> getCurrentScene();

void setCurrentScene(std::shared_ptr<s::AbstractScene> s);

class Scene1 : public s::AbstractScene {
private:
  ll::engine::ShaderProgram shader;
  GLuint vao;
  GLuint vbo;

  float color[3] = {0.0f};

public:
  Scene1(std::shared_ptr<ll::engine::Window> window);
  ~Scene1();
  void updateImgui() override;
  void update() override;
  std::string name() override;
};

}// namespace ll::logic::scenes
