#pragma once
#define GLFW_INCLUDE_NONE

#include "engine/scenes/llscene.hpp"
#include <GLFW/glfw3.h>
#include <memory>

namespace ll::logic::imgui {

void imguiInit(GLFWwindow* window);

void updateImguiFrame(GLFWwindow* window, std::shared_ptr<ll::engine::scene::AbstractScene> scene);

void imguiCleanup();

}// namespace ll::logic::imgui
