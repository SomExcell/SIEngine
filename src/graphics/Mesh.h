#ifndef GRAPHICS_MESH_H_
#define GRAPHICS_MESH_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "SIEngine/GraphicsAPI/OpenGL/Texture.h"
#include "GameObject.h"
#include "SIEngine/Components/Window.h"

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

class Mesh : public GameObject
{
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures);
    void draw() override;

private:
    void setupMesh();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    unsigned int VBO, VAO, EBO;
};

#endif