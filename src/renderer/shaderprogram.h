#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glm/glm.hpp>

#include <map>
#include <string>

class ShaderProgram
{
public:
    explicit ShaderProgram(unsigned int prog);

    void setUniform(std::string const& name, double value1) const;
    void setUniform(std::string const& name, double value1, double value2) const;
    void setUniform(std::string const& name, double value1, double value2, double value3) const;
    void setUniform(std::string const& name, double value1, double value2, double value3, double value4) const;
    void setUniform(std::string const& name, glm::mat2x2 value) const;
    void setUniform(std::string const& name, glm::mat3x3 value) const;
    void setUniform(std::string const& name, glm::mat4x4 value) const;
    void setUniform(std::string const& name, glm::mat2x3 value) const;
    void setUniform(std::string const& name, glm::mat2x4 value) const;
    void setUniform(std::string const& name, glm::mat3x2 value) const;
    void setUniform(std::string const& name, glm::mat3x4 value) const;
    void setUniform(std::string const& name, glm::mat4x3 value) const;
    void setUniform(std::string const& name, glm::mat4x2 value) const;

private:
    std::map<std::string, unsigned int> uniforms;
};

#endif // SHADERPROGRAM_H
