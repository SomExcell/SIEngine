#include "Mesh.h"

#include <stb_image.h>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures):vertices(vertices),indices(indices),textures(textures)
{
    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_boneIDs));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_weights));
    glBindVertexArray(0);
}

void Mesh::draw()
{
    if(_flipTexture){stbi_set_flip_vertically_on_load(true);}
    else{stbi_set_flip_vertically_on_load(false);}
    //Window::objectShader->Use();
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    std::string number;
    std::string name;
    TextureType type;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        type = textures[i].GetType();
        if(type == DIFFUSE)
        {
            number = std::to_string(diffuseNr++);
            name = "material.diffuse";
        }
        else if(type == SPECULAR)
        {
            number = std::to_string(specularNr++);
            name = "material.specular";
        }
        else if(type == NORMAL)
        {
            number = std::to_string(normalNr++);
        }
        else if(type == HEIGHT)
        {
            number = std::to_string(heightNr++);
        }
        // now set the sampler to the correct texture unit
        //Window::objectShader->setInt(name,i);
        // and finally bind the texture
        textures[i].Bind();
    }
    glm::mat4 mat = model;
    mat = glm::translate(mat,position);
    mat = glm::scale(mat,scale);
    mat = glm::rotate(mat,glm::radians(angle), rotate);

    //Window::objectShader->SetMat4("model", mat);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}
