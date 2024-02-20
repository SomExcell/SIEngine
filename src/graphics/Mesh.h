#ifndef GRAPHICS_MESH_H_
#define GRAPHICS_MESH_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 postition;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int m_boneIDs[4];
    float m_weights[4];
};

struct TextureTwo
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureTwo> textures);
    void draw();

private:
    void setupMesh();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureTwo> textures;

    unsigned int VBO, VAO, EBO;
};

#endif