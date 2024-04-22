#ifndef GRAPHICS_MODEL_H_
#define GRAPHICS_MODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "Mesh.h"

class Model
{
public:
    Model(const std::string &path);
    ~Model(){};

    //Model(const Model& rhs){};
    //Model(Model&& rhs){};
    //Model& operator=(const Model& rhs){};
    //Model& operator=(Model&& rhs){};

public:
    void draw();

    void setScale(const glm::vec3 &scale);
    void setRotate(const float& angle, const glm::vec3 &rotate);
    void setPosition(const glm::vec3 &position);
    void setModel(const glm::mat4 &model);
    void outline(const bool &state);
    void setFlipTexture(const bool &state);
    
private:
    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureType typeName);

private:
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
    bool gammaCorrection;
    
};

#endif