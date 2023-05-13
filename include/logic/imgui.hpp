#pragma once

#include <GLFW/glfw3.h>

namespace ll::logic::imgui {

void imguiInit(GLFWwindow* window);

void updateImguiFrame();

void imguiCleanup();

}// namespace ll::logic::imgui
