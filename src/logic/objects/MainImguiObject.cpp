#include "logic/objects.hpp"
#include "logic/scenes.hpp"

#include "engine/engine.hpp"

#include "imgui/imgui.h"

namespace ll::logic::objects {

static int fc = 0;

static bool showMetrics = true;

void MainImguiObject::renderImgui(ll::engine::Window& w) {
  auto windowState = ll::engine::Engine::instance().getWindowState(w);
  fc++;

  // ImGui::ShowDemoWindow(nullptr);
  {
    ImGui::Begin("Info");
    ImGui::BeginChild("scenes", ImVec2(0, ImGui::GetFrameHeightWithSpacing() + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::Button("Clear scene"))
      windowState->setScene(nullptr);

    for (const auto& s: ll::logic::scenes::scenes()) {
      ImGui::SameLine();
      ImGui::PushID(static_cast<int>(s->id()));
      if (ImGui::Button(s->name().c_str()))
        windowState->setScene(s);
      ImGui::PopID();
    }
    // ImGui::SameLine();
    // if (ImGui::Button("Scene 1"))
    //   ll::logic::scenes::setCurrentScene(
    //     std::shared_ptr<ll::engine::scene::AbstractScene>(new ll::logic::scenes::Scene1(window)));
    ImGui::EndChild();
    if (ImGui::Button(showMetrics ? "Hide metrics" : "Show metrics")) {
      showMetrics = !showMetrics;
    }
    if (showMetrics) {
      ImGui::Separator();
      auto&& io = ImGui::GetIO();
      ImGui::Text("F# %d, FR %.2f", fc, io.Framerate);
    }
    ImGui::End();
  }
}

std::shared_ptr<MainImguiObject> MainImguiObject::instance() {
  static std::shared_ptr<MainImguiObject> instance = std::make_shared<MainImguiObject>();
  return instance;
}

}// namespace ll::logic::objects
