#pragma once
#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader();
    ~Shader();

    bool Load(const std::string& vertexPath, const std::string& fragmentPath);
    void Use();
    GLuint GetProgram() const { return mProgram; }

private:
    GLuint mProgram;
    GLuint CompileShader(const std::string& source, GLenum shaderType);
    std::string LoadFile(const std::string& path);
};