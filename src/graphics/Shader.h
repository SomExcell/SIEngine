#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
    Shader(const std::string &vertexShader, const std::string &fragmentShader);

    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader(Shader&& rhs) noexcept;
    Shader& operator=(Shader&) = delete;
    Shader& operator=(Shader&& rhs) noexcept;
    ~Shader();

    GLuint getID();
    void use();
    void load_shader(const std::string &vertexShader, const std::string &fragmentShader);
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);

    bool isCompiled = false;
    GLuint ID = 0;
};

#endif