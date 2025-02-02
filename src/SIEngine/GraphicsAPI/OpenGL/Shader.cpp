#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    LoadShaders(vertexShader, fragmentShader);
}

void Shader::LoadShaders(const std::string &vertexShaderFile, const std::string &fragmentShaderFile)
{
    auto vertexCode = ReadShaderCode(vertexShaderFile);
    auto fragmentCode = ReadShaderCode(fragmentShaderFile);

    if(vertexCode.has_value() && fragmentCode.has_value())
    {
        auto vertexShader = CreateShader(*vertexCode, GL_VERTEX_SHADER);
        auto fragmentShader = CreateShader(*fragmentCode, GL_FRAGMENT_SHADER);

        if(vertexShader.has_value() && fragmentShader.has_value())
        {
            LinkShaders(*vertexShader, *fragmentShader);
        }
    }
}

std::optional<std::string> Shader::ReadShaderCode(const std::string& shaderFilePath)
{
    try
    {
        std::ifstream shaderFile{shaderFilePath.c_str()};
        shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "Shader file is not successfully read" << std::endl;
        std::cerr << "Error code: " <<  e.code().value() << " (" << e.code().message() << ")" << std::endl;
        return {};
    }
}

std::optional<GLuint> Shader::CreateShader(const std::string& source, const GLenum shaderType)
{
    GLuint shaderID = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    return HasShaderErrors(shaderID, GL_COMPILE_STATUS) ? std::nullopt : std::optional<GLuint>{shaderID};
}

void Shader::LinkShaders(const GLuint &vertexShader, const GLuint &fragmentShader)
{
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);

    glLinkProgram(id);
    HasShaderErrors(id, GL_LINK_STATUS);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

bool Shader::HasShaderErrors(const GLuint &shaderId, GLenum type)
{
    GLint success;
    char infoLog[1024];

    if(type == GL_COMPILE_STATUS)
    {
        glGetShaderiv(shaderId, type, &success);
        if (success == GL_FALSE)
        {
            glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
            std::cerr << "Shader error: " << infoLog << std::endl;
            return true;
        }
    }
    else if(type == GL_LINK_STATUS)
    {
        glGetProgramiv(shaderId, type, &success);
        if(success == GL_FALSE)
        {
            glGetProgramInfoLog(shaderId, 1024, nullptr, infoLog);
            std::cerr << "Shader error: " << infoLog << std::endl;
            return true;
        }
    }

    return false;
}

void Shader::Use() const
{
    glUseProgram(id);
}

void Shader::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
