#include "shaderprogram.h"

#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

#include <iostream>
#include <vector>

#define GET_LOCATION_MACRO \
    if (uniforms.find(name) == uniforms.end()) { std::cout << "rejecting: " + name << "\n"; return; }; \
    unsigned int location = uniforms.find(name)->second;

ShaderProgram::ShaderProgram(unsigned int prog)
{
    GLint numUniforms = 0;
    GLint maxUniformName = 0;

    glGetProgramiv(prog, GL_ACTIVE_UNIFORMS, &numUniforms);
    glGetProgramiv(prog, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformName);

    std::vector<GLchar> nameData(maxUniformName);

    for (int u = 0; u < numUniforms; u++) {
        GLint arraySize = 0;
        GLenum type = 0;
        GLsizei actualLength = 0;

        glGetActiveUniform(prog,u,nameData.size(),&actualLength,&arraySize,&type,nameData.data());

        std::string name(nameData.data(), actualLength);

        uniforms[name] = u;
    }
}

void ShaderProgram::setUniform(const std::string &name, double value1) const
{
    GET_LOCATION_MACRO;

    glUniform1f(location,value1);
}

void ShaderProgram::setUniform(const std::string &name, double value1, double value2) const
{
    GET_LOCATION_MACRO;

    glUniform2f(location, value1, value2);
}

void ShaderProgram::setUniform(const std::string &name, double value1, double value2, double value3) const
{
    GET_LOCATION_MACRO;

    glUniform3f(location, value1, value2, value3);
}

void ShaderProgram::setUniform(const std::string &name, double value1, double value2, double value3, double value4) const
{
    GET_LOCATION_MACRO;

    glUniform4f(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniform(const std::string &name, glm::mat2x2 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix2fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat3x3 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix3fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat4x4 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat2x3 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix2x3fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat2x4 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix2x4fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat3x2 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix3x2fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat3x4 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix3x4fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat4x3 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix4x3fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, glm::mat4x2 value) const
{
    GET_LOCATION_MACRO;

    glUniformMatrix4x2fv(location, 1, false, glm::value_ptr(value));
}
