#include "logic/objects.hpp"

// #include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace ll::logic::objects::scene1 {

void SimpleTriangleImgui::renderImgui(ll::engine::Window& w) {
  ImGui::Begin("Simple Triangle");
  ImGui::SliderFloat3("RGB", /* glm::value_ptr(_t.color()) */ &_t.color().x, 0.0f, 1.0f);
  ImGui::End();
}

}// namespace ll::logic::objects::scene1
