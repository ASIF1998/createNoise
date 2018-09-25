#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>

#include "noise.hpp"

#include "texture.hpp"

GLuint vertHandle, fragHandle, programHandle;

void scene (SDL_Window* window) {
    glUseProgram (programHandle);
    
    GLubyte* data = noise::create2DMapNoise(2.0, .3, .6, 200, 300);
    
    texture noiseTexture (data, 200, 300);
    noiseTexture.bind();
    
    delete [] data;
    
    glUniform1i (glGetUniformLocation (programHandle, "ourTexture"), 0);
    
    GLfloat texCoords[] = {
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,
        0.0, 0.0,
        1.0, 1.0,
        1.0, 0.0
    };
    
    float positionData[] = {
        -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    
    GLuint positionHandler, textCooedHandle;
    
    glGenBuffers (1, &textCooedHandle);
    glGenBuffers (1, &positionHandler);
    
    if (!positionHandler || !textCooedHandle)
        throw std::runtime_error ("Не получилось создать vbo.");
    
    glBindBuffer (GL_ARRAY_BUFFER, positionHandler);
    glBufferData (GL_ARRAY_BUFFER, sizeof(positionData), positionData,GL_STATIC_DRAW);
    
    glBindBuffer (GL_ARRAY_BUFFER, textCooedHandle);
    glBufferData (GL_ARRAY_BUFFER, sizeof(texCoords), texCoords,GL_STATIC_DRAW);
    
    
    GLuint vaoHandler = 0;
    
    glGenVertexArrays (1, &vaoHandler);
    
    if (!vaoHandler)
        throw ("Не получилось создать vao");
    
    glBindVertexArray (vaoHandler);;
    
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    
    glBindBuffer (GL_ARRAY_BUFFER, positionHandler);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    glBindBuffer (GL_ARRAY_BUFFER, textCooedHandle);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    bool stay = true;
    SDL_Event event;
    
    while (stay) {
        while (SDL_PollEvent (&event))
            if (event.type == SDL_QUIT)
                stay = false;
        
        glClear (GL_COLOR_BUFFER_BIT);
        glDrawArrays (GL_TRIANGLES, 0, 6);
        SDL_GL_SwapWindow (window);
    }
}

void deleteShaderSAndShaderProgram () noexcept {
    glDeleteProgram (programHandle);
    glDeleteShader (vertHandle);
    glDeleteShader (fragHandle);
}

void createShaderProgram () throw (std::runtime_error) {
    programHandle = glCreateProgram ();
    
    if (!programHandle)
        throw std::runtime_error ("Error create shader program");
    
    glAttachShader (programHandle, vertHandle);
    glAttachShader (programHandle, fragHandle);
    
    glLinkProgram (programHandle);
    
    GLint res;
    glGetProgramiv (programHandle, GL_LINK_STATUS, &res);
    
    if (!res)
        throw std::runtime_error ("Error linl shader program");
}

std::string readFile (const std::string& fileName) {
    std::ifstream f (fileName);
    f.seekg (0, std::ios::end);
    size_t size = f.tellg();
    std::string s (size, ' ');
    f.seekg (0);
    f.read (&s[0], size);
    return s;
}

inline void checkCompileShader (GLuint desc) throw (std::runtime_error) {
    GLint res;
    glGetShaderiv (desc, GL_COMPILE_STATUS, &res);
    
    if (!res)
        throw std::runtime_error ("Error conpile shader");
}

void createShader () throw (std::runtime_error) {
    vertHandle = glCreateShader (GL_VERTEX_SHADER);
    fragHandle = glCreateShader (GL_FRAGMENT_SHADER);
    
    if (!vertHandle || !fragHandle)
        throw std::runtime_error ("Error create shader");
    
    std::string vertCodeString (readFile("/Users/asifmamedov/Desktop/useTextureOpenGL/i/i/basic.vert"));
    std::string fragCodeString (readFile("/Users/asifmamedov/Desktop/useTextureOpenGL/i/i/basic.frag"));
    
    const char* vertCode = vertCodeString.c_str();
    const char* fragCode = fragCodeString.c_str();
    
    glShaderSource (vertHandle, 1, &vertCode, nullptr);
    glShaderSource (fragHandle, 1, &fragCode, nullptr);
    
    glCompileShader (vertHandle);
    glCompileShader (fragHandle);
    
    checkCompileShader (vertHandle);
    checkCompileShader (fragHandle);
}

inline void error () throw (std::runtime_error) {
    std::string msg (SDL_GetError());
    SDL_ClearError ();
    throw msg;
}

inline void setOpenGLAttributes () noexcept {
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
}

inline void windowDestroy (SDL_Window* window) noexcept {
    SDL_DestroyWindow (window);
}

SDL_Window* creatwWindow (const char* windowName) throw (std::runtime_error) {
    SDL_Window* window = SDL_CreateWindow (windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    
    if (!window)
        error ();
        
        return window;
}

inline void quit () noexcept {
    SDL_Quit ();
}

inline void init () throw (std::runtime_error) {
    if (SDL_Init (SDL_INIT_EVERYTHING))
        error ();
        }

int main () {
    try {
        init ();
        SDL_Window* window = creatwWindow ("Using Texture.");
        setOpenGLAttributes ();
        SDL_GLContext context = SDL_GL_CreateContext (window);
        glewExperimental = GL_TRUE;
        glewInit ();
        createShader ();
        createShaderProgram ();
        scene(window);
        deleteShaderSAndShaderProgram ();
        SDL_GL_DeleteContext (context);
        windowDestroy (window);
        quit ();
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what () << std::endl;
    }
    return 0;
}
