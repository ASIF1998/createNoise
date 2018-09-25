#include "noise.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

GLubyte* noise::create2DMapNoise(float baseFreq, float persistence, float surfaceDepth, int w, int h) {
    GLubyte *data = new GLubyte[ w * h * 4 ];
    
    for( int row = 0; row < h; row++ ) {
        for( int col = 0 ; col < w; col++ ) {
            float x = (1.0f / (w - 1)) * col;
            float y = (1.0f / (h - 1)) * row;
            float sum = 0.0f;
            float freq = baseFreq;
            float amplitude = persistence;
            
            for(int oct = 0; oct < 4; oct++ ) {
                glm::vec2 p(x * freq , y * freq + 10.0);
                sum += glm::simplex(p) * amplitude;
                
                // Полученное значение приводится от 0 до 1
                float result = (sum + surfaceDepth) / 2.0f;
                result = (result > 1.0f ? 1.0f : (result < 0.0 ? 0.0 : result));
                
                data[((row * w + col) * 4) + oct] = (GLubyte) ( result * 255 );
                freq *= 2.0;
                amplitude *= persistence;
            }
        }
    }
    return data;
}
