#pragma once
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "engine/gl/shader.hpp"
#include "engine/scenes/llscene.hpp"
#include "engine/window_state.hpp"

#include <memory>
#include <string>
#include <utility>

namespace ll::logic::scenes {

namespace s = ll::engine::scene;

void init(std::shared_ptr<engine::WindowState> w);

const std::unordered_map<std::string, std::shared_ptr<s::AbstractScene>>& scenes();

class MainScene : public s::AbstractScene {
public:
  MainScene(std::shared_ptr<engine::Window> window) : s::AbstractScene(std::move(window)) {}
  std::string name() override;
};

class Scene1 : public s::AbstractScene {
public:
  Scene1(std::shared_ptr<engine::Window> window) : s::AbstractScene(std::move(window)) {}
  std::string name() override;
};

}// namespace ll::logic::scenes
