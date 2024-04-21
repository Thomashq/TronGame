#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Shader.h"


class Model
{
public:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    Model(const char *path);

    void Draw(Shader &shader);

private:

    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh * mesh, const aiScene * scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};