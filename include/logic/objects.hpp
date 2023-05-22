#pragma once

#include "engine/scenes/llscene.hpp"
#include "engine/window.hpp"

namespace ll::logic::objects {

class MainImguiObject : public ll::engine::scene::RenderableObject {
public:
  void renderImgui(ll::engine::Window& w) override;

  static std::shared_ptr<MainImguiObject> instance();
};

}// namespace ll::logic::objects
