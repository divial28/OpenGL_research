#ifndef SHADER_H
#define SHADER_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    
    ~Shader();

    void Use();

    GLuint getProgram() { return program; }

private:
    const GLchar* const* readSource(const GLchar* sourcePath);

    void checkShader(GLuint shader, const GLchar* shaderType);

    void checkProgram(GLuint program);

private:
    GLuint          program;
    GLint           success;
    GLchar          infoLog[512];
    std::string     source;
    const GLchar    * sourcePtr;
};

#endif