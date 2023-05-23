#pragma once

#include "engine/scenes/llscene.hpp"
#include "engine/window.hpp"
#include "logic/scenes.hpp"

namespace ll::logic::objects {

class MainImguiObject : public ll::engine::scene::RenderableObject {
public:
  void renderImgui(ll::engine::Window& w) override;

  static std::shared_ptr<MainImguiObject> instance();
};

namespace scene1 {

  class SimpleTriangle : public ll::engine::scene::RenderableObject {
  private:
    ll::engine::ShaderProgram _shader;
    GLuint _vao = 0;
    GLuint _vbo = 0;
    glm::vec3 _color = {0.0f, 0.0f, 0.0f};

  public:
    SimpleTriangle();
    ~SimpleTriangle();

    void render(ll::engine::Window& w) override;
    glm::vec3& color() { return _color; }
  };

  class SimpleTriangleImgui : public ll::engine::scene::RenderableObject {
  private:
    SimpleTriangle& _t;

  public:
    SimpleTriangleImgui(SimpleTriangle& t) : _t(t) {}

    void renderImgui(ll::engine::Window& w) override;
  };

}// namespace scene1

}// namespace ll::logic::objects
