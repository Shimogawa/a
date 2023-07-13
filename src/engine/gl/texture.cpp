#include "engine/gl/texture.hpp"

#include "stb_image.h"

#include <cstdint>

namespace ll::engine {

Texture::Texture(const std::string& path) {
  uint8_t* data = stbi_load(path.c_str(), &this->_width, &this->_height, &this->_nChannels, 0);
  if (!data) {
    this->_hasError = true;
    this->_message = fmt::format("failed to load image {}", path);
    return;
  }
  glGenTextures(1, &this->_id);
  glBindTexture(GL_TEXTURE_2D, this->_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  this->_hasError = false;
}

Texture::~Texture() {
  glDeleteTextures(1, &this->_id);
}

void Texture::use(GLenum idx) {
  glActiveTexture(idx);
  glBindTexture(GL_TEXTURE_2D, this->_id);
}

}// namespace ll::engine
