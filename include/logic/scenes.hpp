#pragma once
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "engine/gl/shader.hpp"
#include "engine/gl/texture.hpp"
#include "engine/scenes/llscene.hpp"
#include "engine/window_state.hpp"

#include <memory>
#include <string>
#include <utility>

namespace ll::logic::scenes {

namespace s = ll::engine::scene;

void init(const std::shared_ptr<engine::WindowState>& w);

void cleanup();

const std::unordered_map<std::string, std::shared_ptr<s::AbstractScene>>& scenes();

class MainScene : public s::AbstractScene {
public:
  MainScene(std::shared_ptr<engine::Window> window) : s::AbstractScene(std::move(window)) {}
  std::string name() override;
};

class Scene1 : public s::AbstractScene {
public:
  Scene1(std::shared_ptr<engine::Window> window) : s::AbstractScene(std::move(window)) {}
  std::string name() override { return "Simple Triangle"; }
};

class Scene2 : public s::AbstractScene {
public:
  Scene2(std::shared_ptr<engine::Window> window) : s::AbstractScene(std::move(window)) {}
  std::string name() override { return (char*) u8"原神，启动！"; }
};

}// namespace ll::logic::scenes
