#pragma once

#include "engine/scenes/llscene.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

namespace ll::logic::imgui {

void imguiInit(std::shared_ptr<ll::engine::Window> window);

void updateImguiFrame(GLFWwindow* window, std::shared_ptr<ll::engine::scene::AbstractScene> scene);

void imguiCleanup();

}// namespace ll::logic::imgui
