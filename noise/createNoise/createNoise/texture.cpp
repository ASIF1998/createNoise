#include "texture.hpp"

#include <string.h>

texture::texture(const GLubyte* data, GLint w, GLint h) : _w(w), _h(h), _data(new GLubyte [w * h * 4]) {
    memcpy(_data, data, w * h * 4);
    
    glGenTextures(1, &_texID);
    glBindTexture(GL_TEXTURE_2D, _texID);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, w, h);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA,GL_UNSIGNED_BYTE, _data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

texture::~texture() {
    delete [] _data;
}

void texture::bind(GLint slot) const noexcept {
    glActiveTexture (GL_TEXTURE0 + slot);
    glBindTexture (GL_TEXTURE_2D, _texID);
}

void texture::unbind () const noexcept {
    glBindTexture (GL_TEXTURE_2D, 0);
}

GLint texture::getWidth() const noexcept {
    return _w;
}

GLint texture::getHeight() const noexcept {
    return _h;
}
