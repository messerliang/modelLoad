#include "Model3D.h"

#include "functions.h"




Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int> indices, std::vector< TextureInfo> textures) :
	m_vertices(vertices), m_indices(indices), m_textures(textures), m_meshName("None")
{
	setupMesh();
}

Mesh::Mesh(const std::string&name, std::vector<Vertex>& vertices, std::vector<unsigned int> indices, std::vector< TextureInfo> textures) :
	m_vertices(vertices), m_indices(indices), m_textures(textures), m_meshName(name)
{
	setupMesh();
}

void Mesh::setupMesh() {
	// ��������Ҫ�Ķ���
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glGenBuffers(1, &EBO));

	// �� vertex buffer �е����ݣ����䵽 GPU
	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW));

	// �� indices �������䵽 GPU
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(unsigned int), &this->m_indices[0], GL_STATIC_DRAW));

	// ���ö�������ָ��
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));

	// ���÷�������
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)));

	// ������������
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords)));

	GLCall(glBindVertexArray(0));

}

void Mesh::Draw(Shader& shader) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	std::unordered_map<std::string, int> texCnt;

	// �������е�������Ϣ
	for (unsigned int i = 0; i < this->m_textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::stringstream ss;
		std::string number;
		std::string name = this->m_textures[i].type;
		if (name == "texture_diffuse") {
			ss << diffuseNr++;
		}
		else if (name == "texture_specular") {
			ss << specularNr++;
		}
		number = ss.str(); // �ַ�������ֵ

		texCnt[name]++;

		// ���Ӧ�� uniform ������ֵ
		std::string sample2DTexName = (name + number);
		//std::cout <<"type: " << this->m_textures[i].type << ", " << "shader uniform: " << sample2DTexName << std::endl;
		GLCall(glUniform1f(glGetUniformLocation(shader.m_shaderProgramId, sample2DTexName.c_str()), i));
		GLCall(glBindTexture(GL_TEXTURE_2D, this->m_textures[i].id));
	}


	// ���� Mesh
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0));
	glBindVertexArray(0);

	// �ǵð����е� texture �ȹص�
	//for (GLuint i = 0; i < this->m_textures.size(); i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i);
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}

}


Model3D::Model3D(const std::string& path) {
	loadModel(path);
}

void Model3D::Draw(Shader& shader) {
	for (unsigned int i = 0; i < meshes.size(); ++i) {
		meshes[i].Draw(shader);
	}
}

void Model3D::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));
	this->processNode(scene->mRootNode, scene);

}
void Model3D::processNode(aiNode* node, const aiScene* scene)
{
	//std::cout << utf8_to_ansi(node->mName.C_Str()) << ", node mesh num: " << node->mNumMeshes << ", node child num: " << node->mNumChildren << std::endl;
	// ������е� Mesh ��Ϣ
	for (uint32_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	// �ݹ�ڵ������ڵ�
	for (uint32_t i = 0; i < node->mNumChildren; ++i) {
		this->processNode(node->mChildren[i], scene);
	}
}
// �� assimp ��mesh����ת��Ϊ����ǰ�涨�������
Mesh Model3D::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<TextureInfo> textures;
	std::string name = mesh->mName.C_Str();
	//std::cout << utf8_to_ansi(name) << " vertex num: " << mesh->mNumVertices << std::endl;
	for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
		// ���������ꡢ���ߡ���������
		Vertex vertex;
		glm::vec3 vec;
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vertex.Position = vec;

		vec.x = mesh->mNormals[i].x;
		vec.y = mesh->mNormals[i].y;
		vec.z = mesh->mNormals[i].z;
		vertex.Normal = vec;

		// һ�� vertex ���ܶ�Ӧ������ʣ��������ǹ���ֻ���ǵ�һ��
		if (mesh->mTextureCoords[0]) {
			glm::vec2 coords;
			coords.x = mesh->mTextureCoords[0][i].x;
			coords.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = coords;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	// ����������
	for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// ������ʣ�����������;��淴��
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<TextureInfo> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffues");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<TextureInfo> specularMaps = this->loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(utf8_to_ansi(name),vertices, indices, textures);
}


std::vector<TextureInfo> Model3D::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<TextureInfo> textures;

	for (uint32_t i = 0; i < mat->GetTextureCount(type); ++i) {
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string std_str = str.C_Str();
		if (existTextures.count(std_str)) {
			continue;
		}
		std::string imgPath = this->directory + "/" + str.C_Str();

		Texture texObj(imgPath);

		if (-1 == texObj.GetId()) {
			continue;
		}
		TextureInfo texture;
		texture.id = texObj.GetId();
		texture.type = typeName;
		texture.path = str;

		textures.push_back(texture);

		existTextures[std_str] = texture.id;
	}
	return textures;
}
