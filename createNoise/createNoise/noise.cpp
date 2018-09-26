#include "noise.hpp"

#include <glm/gtc/noise.hpp>

GLubyte* noise::create2DMapNoise(float baseFreq, float persistence, float surfaceDepth, int octave, glm::vec2 shift, int w, int h) {
    GLubyte *data = new GLubyte[ w * h * 4 ];
    
    for(int i = 0; i < w; i++) {
        for(int j = 0 ; j < h; j++) {
            float x = (1.0f / (w - 1)) * i;
            float y = (1.0f / (h - 1)) * j;
            float sum = 0.0f;
            float freq = baseFreq;
            float amplitude = persistence;
            
            // 0 <= shift << 262142.0f
//            glm::vec2 shift (262142.0f);
            
            for(int oct = 0; oct < octave; oct++ ) {
                glm::vec2 p (x * freq, y * freq);
                p += shift;
                sum += glm::simplex(p) * amplitude;
                
                // Полученное значение приводится от 0 до 1
                float result = (sum + surfaceDepth) / 2.0f;
                result = (result > 1.0f ? 1.0f : (result < 0.0 ? 0.0 : result));
                
                data[((j * w + i) * 4)] = (GLubyte) ( result * 255 );
                freq *= 2.0;
                amplitude *= persistence;
            }
            
            data[((j * w + i) * 4) + 1] = data[((j * w + i) * 4) + 2] = data[((j * w + i) * 4) + 3] = data[((j * w + i) * 4)];
        }
    }
    return data;
}
