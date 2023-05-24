#include "logic/objects.hpp"
#include "logic/scenes.hpp"

#include "engine/engine.hpp"

#include "imgui/imgui.h"

namespace ll::logic::objects {

static int fc = 0;

static bool showMetrics = true;

void MainImguiObject::renderImgui(ll::engine::Window& w) {
  auto windowState = ll::engine::Engine::instance().getWindowState(w);
  auto& scenes = ll::logic::scenes::scenes();
  auto& mainScene = scenes.at("Main Scene");
  fc++;

  // ImGui::ShowDemoWindow(nullptr);
  {
    ImGui::Begin("Info");
    ImGui::BeginChild("scenes", ImVec2(0, ImGui::GetFrameHeightWithSpacing() + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::Button((const char*) u8"Main scene"))
      windowState->setScene(mainScene);

    for (const auto& x: scenes) {
      if (x.second->id() == mainScene->id())
        continue;
      ImGui::SameLine();
      ImGui::PushID(static_cast<int>(x.second->id()));
      if (ImGui::Button(x.second->name().c_str()))
        windowState->setScene(x.second);
      ImGui::PopID();
    }
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
