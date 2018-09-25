#ifndef texture_hpp
#define texture_hpp

#include <GL/glew.h>

class texture {
private:
    GLuint _texID;
    GLubyte* _data;
    GLint _w, _h;
    
public:
    texture (const GLubyte* daya, GLint w, GLint h);
    ~texture();
    
    void bind (GLint slot = 0) const noexcept;
    void unbind () const noexcept;
    
    GLint getWidth () const noexcept;
    GLint getHeight () const noexcept;
};

#endif /* texture_hpp */
