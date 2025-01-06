#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <optional>
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

public:
    void Use() const;

private:
    void LinkShaders(const GLuint &vertexShader, const GLuint &fragmentShader);
    void LoadShaders(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

private:
    static std::optional<std::string> ReadShaderCode(const std::string& shaderFilePath);
    static std::optional<GLuint> CreateShader(const std::string& source, GLenum shaderType);
    static bool HasShaderErrors(const GLuint &shaderId, GLenum type);

public:
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVec2(const std::string &name, const glm::vec2 &value) const;
    void SetVec3(const std::string &name, const glm::vec3 &value) const;
    void SetVec4(const std::string &name, const glm::vec4 &value) const;
    void SetMat2(const std::string &name, const glm::mat2 &mat) const;
    void SetMat3(const std::string &name, const glm::mat3 &mat) const;
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    bool isCompiled = false;
    GLuint ID = 0;
};

#endif