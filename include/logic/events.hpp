#pragma once

#include "GLFW/glfw3.h"
#include "engine/events/llevents.hpp"
#include <memory>

namespace ll::logic::events {

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

void setupCallbacks(GLFWwindow* window);

void processEvents();

}// namespace ll::logic::events
