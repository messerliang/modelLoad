#pragma once
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <sstream>
#include <cstdint>
#include <unordered_map>


#include "GL_Error.h"
#include "Shader.h"
#include "Texture.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureInfo {
	unsigned int id;
	std::string type;
	aiString path;
};


class Mesh {
public:
	std::string m_meshName;

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector< TextureInfo> m_textures;
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int> indices, std::vector< TextureInfo> textures);
	Mesh(const std::string& name, std::vector<Vertex>& vertices, std::vector<unsigned int> indices, std::vector< TextureInfo> textures);
private:
	unsigned int VAO, VBO, EBO; // EBO 是 indices的 id
	void setupMesh();
public:
	void Draw(Shader& shader);
};



class Model3D {
public:
	Model3D(const std::string& path);
	void Draw(Shader& shader);
public:
	std::vector<Mesh> meshes;
	std::string directory;
	std::unordered_map<std::string, uint32_t> existTextures;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	// 将 assimp 的mesh数据转换为我们前面定义的类型
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureInfo> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};