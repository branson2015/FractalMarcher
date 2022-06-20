#include <string>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

#include "shader.hpp"



Shader::Shader() {

}

Shader::Shader(const std::string &path_vs, const std::string &path_fs){
    if(!load(path_vs, path_fs)){
        return;
    }
}

Shader::~Shader() {
    if(program)
        glDeleteProgram(program);
}

bool Shader::createProgram(const std::string &vertexsrc, const std::string &fragmentsrc){
    vertexSource = vertexsrc;
    fragmentSource = fragmentsrc;

    if(!createShader(vertexSource, GL_VERTEX_SHADER, vertexShader)){
        return false;
    }
    if(!createShader(fragmentsrc, GL_FRAGMENT_SHADER, fragmentShader)){
        return false;
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if(isLinked == GL_FALSE){
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar *infoLog = new GLchar[maxLength];
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        std::cerr << infoLog << std::endl;

        // LOG(infoLog);

        delete[] infoLog;

        return false;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return true;
}

bool Shader::load(const std::string &path_vs, const std::string &path_fs){
    return createProgram(readFile(path_vs), readFile(path_fs));
}

bool Shader::createShader(const std::string &shadersrc, GLenum shaderType, GLuint &returnShaderHandle){
    GLuint shader = glCreateShader(shaderType);
    const GLchar *source = (const GLchar*)shadersrc.c_str();

    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar *infoLog = new GLchar[maxLength];
            glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

            glDeleteShader(shader);

            std::cerr << infoLog << std::endl;
            //LOG(infoLog);

            delete[] infoLog;
            
            returnShaderHandle = static_cast<GLuint>(-1);
            return false;
    }

    returnShaderHandle = shader;
    return true;
}

std::string Shader::readFile(const std::string &fn){
    std::ifstream f(fn);

    if(!f.is_open()){
        std::cerr << "File " << fn.c_str() << " could not be opened" << std::endl;
        // LOG("File %s could not be opened", fn.c_str());
        return "";
    }

    std::string str;

    f.seekg(0, std::ios::end);
    str.reserve(f.tellg());
    f.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    return str;
}
