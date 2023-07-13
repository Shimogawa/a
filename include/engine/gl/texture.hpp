#pragma once

#include <cassert>

#include <glad/glad.h>

#include "engine/gl/gl.hpp"

namespace ll::engine {

class Texture : public gl::GLUsableObject {
public:
  Texture(const std::string& path);
  ~Texture() override;

  void use() override { assert(false && "you can't use this function"); }
  void use(GLenum index) override;

private:
  int _width;
  int _height;
  int _nChannels;
};

}// namespace ll::engine
