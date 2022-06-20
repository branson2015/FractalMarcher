#ifndef FRACTALMARCHER_SHADER_HPP
#define FRACTALMARCHER_SHADER_HPP

#include <string>

#include <glad/glad.h>

class Shader {
public:
    Shader();
    Shader(const std::string &path_vs, const std::string &path_fs);
    ~Shader();

    bool load(const std::string &path_vs, const std::string &path_fs);
    void bind(){ glUseProgram(program); }
    void unbind(){ glUseProgram(0); }
private:
    bool createProgram(const std::string &vertexsrc, const std::string &fragmentsrc);
    bool createShader(const std::string &src, GLenum shaderType, GLuint &returnShaderHandle);

    

    std::string vertexSource;
    std::string fragmentSource;

    GLuint vertexShader;
    GLuint fragmentShader;

    GLuint program;
    std::string readFile(const std::string &fn);

};

#endif