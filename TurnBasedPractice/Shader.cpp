#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
    : mProgram(0) {}

Shader::~Shader() {
    if (mProgram != 0) {
        glDeleteProgram(mProgram);
    }
}

bool Shader::Load(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = LoadFile(vertexPath);
    std::string fragmentCode = LoadFile(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cout << "Failed to load shader source code." << std::endl;
        return false;
    }

    GLuint vertexShader = CompileShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(fragmentCode, GL_FRAGMENT_SHADER);

    if (vertexShader == 0 || fragmentShader == 0) {
        return false;
    }

    // Create program and attach shaders
    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(mProgram, 512, nullptr, infoLog);
        std::cout << "Shader Program Linking Failed:\n" << infoLog << std::endl;
        return false;
    }

    // Shaders no longer needed after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void Shader::Use() {
    if (mProgram != 0) {
        glUseProgram(mProgram);
    }
}

GLuint Shader::CompileShader(const std::string& source, GLenum shaderType) {
    const char* src = source.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::string typeStr = (shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cout << typeStr << " Shader Compilation Failed:\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

std::string Shader::LoadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Failed to open shader file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}