#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    load_shader(vertexShader,fragmentShader);
}

Shader::Shader(unsigned int id) : ID(id){}

Shader& Shader::operator=(Shader&& rhs) noexcept
{
    if(this == &rhs)
    {
        return *this;
    }
    glDeleteProgram(ID);
    ID = rhs.ID;
    isCompiled = rhs.isCompiled;

    rhs.ID = 0;
    rhs.isCompiled = false;
    return *this;
}

Shader::Shader(Shader&& rhs) noexcept
{
    ID = rhs.ID;
    isCompiled = rhs.isCompiled;

    rhs.ID = 0;
    rhs.isCompiled = false;
}

Shader::~Shader()
{
    //glDeleteProgram(ID);
}

void Shader::load_shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexShader);
        fShaderFile.open(fragmentShader);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "Caught an ios_base::failure.\n"
                      << "Error code: " << e.code().value()
                      << " (" << e.code().message() << ")\n"
                      << "Error category: " << e.code().category().name() << "\n";
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            return;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    
    GLuint vertex, fragment;
    
    if(!createShader(vShaderCode,GL_VERTEX_SHADER,vertex))
    {
        std::cerr << "VERTEX SHADER compile-time error" << std::endl;
    }
    
    if(!createShader(fShaderCode,GL_FRAGMENT_SHADER,fragment))
    {
        std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
    }
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

bool Shader::createShader(const std::string& source, const GLenum shaderType,GLuint& shaderID)
{
    shaderID = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

GLuint Shader::getID()
{
    return ID;
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

Shader* load_shader(const std::string &vertexFile, const std::string &fragmentFile) {
	// Reading Files
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		vShaderFile.open(vertexFile);
		fShaderFile.open(fragmentFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure& e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cerr << "SHADER::VERTEX: compilation failed" << std::endl;
		std::cerr << infoLog << std::endl;
		return nullptr;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
		std::cerr << infoLog << std::endl;
		return nullptr;
	}

	// Shader Program
	GLuint id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cerr << "SHADER::PROGRAM: linking failed" << std::endl;
		std::cerr << infoLog << std::endl;

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return nullptr;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return new Shader(id);
}