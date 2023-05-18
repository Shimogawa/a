#include "engine/scenes/llscene.hpp"
#include "GLFW/glfw3.h"

#include <atomic>
#include <stdint.h>

namespace ll::engine::scene {

static std::atomic_uint64_t uniqueid = 100;

AbstractScene::AbstractScene(GLFWwindow* window) : EngineObject(window) {
  _id = uniqueid.fetch_add(1);
}

AbstractScene::~AbstractScene() {}

}// namespace ll::engine::scene
