#ifndef noise_hpp
#define noise_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>

class noise {
public:
    static GLubyte* create2DMapNoise (float baseFreq = 4.0f, float persistance = 0.5f, float surfaceDepth = 1.0f, int octave = 4, glm::vec2 shift = glm::vec2(0.0f, 0.0f), int w = 128, int h = 128);
};

#endif /* noise_hpp */
