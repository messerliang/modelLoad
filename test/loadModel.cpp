
// GLEW
#define GLEW_STATIC
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
#include <windows.h>
#include <io.h>
#include <fcntl.h>


#include "GL_Error.h"
#include "Shader.h"
#include "Texture.h"
#include "constants.h"
#include "Render.h"
#include "Model3D.h"
#include "functions.h"


#if 0

int main() {

	SetConsoleOutputCP(CP_UTF8);     // 设置输出编码

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	// 配置使用的版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Window", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	camera.bindCallbackToWindow(window);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, screenWidth, screenHeight);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);





	Vertex m_vertices[] = {
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.1f, 0.1f, 0.2f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.5f, 0.3f, 0.1f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.7f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.3f, 0.8f, 0.6f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.2f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 0.5f,  0.5f, 0.5f), glm::vec3(0.5f, 0.3f, 0.1f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f, -0.5f, 0.5f), glm::vec3(0.7f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(0.3f, 0.8f, 0.6f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f,  -0.5f), glm::vec3(0.1f, 0.1f, 0.2f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f,   0.5f), glm::vec3(0.5f, 0.3f, 0.1f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f,   0.5f), glm::vec3(0.7f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f,  -0.5f), glm::vec3(0.3f, 0.8f, 0.6f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f,  -0.5f), glm::vec3(0.1f, 0.1f, 0.2f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(0.5f,  0.5f,   0.5f), glm::vec3(0.5f, 0.3f, 0.1f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f,   0.5f), glm::vec3(0.7f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(0.5f,  0.5f,  -0.5f), glm::vec3(0.3f, 0.8f, 0.6f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.1f, 0.1f, 0.2f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 0.5f, 0.5f,  0.5f), glm::vec3(0.5f, 0.3f, 0.1f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f, 0.5f, -0.5f), glm::vec3(0.7f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f, 0.5f,  0.5f), glm::vec3(0.3f, 0.8f, 0.6f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.1f, 0.1f, 0.2f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.5f, 0.3f, 0.1f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.7f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.3f, 0.8f, 0.6f), glm::vec2(0.0f, 1.0f)},
	};
	unsigned int m_indices[] = {
		0, 1, 2,
		0, 1, 3,

		4 + 0, 4 + 1, 4 + 2,
		4 + 0, 4 + 1, 4 + 3,
		8 + 0, 8 + 1, 8 + 2,
		8 + 0, 8 + 1, 8 + 3,
		12 + 0, 12 + 1, 12 + 2,
		12 + 0, 12 + 1, 12 + 3,
		16 + 0, 16 + 1, 16 + 2,
		16 + 0, 16 + 1, 16 + 3,
		20 + 0, 20 + 1, 20 + 2,
		20 + 0, 20 + 1, 20 + 3,
	};
	unsigned int VA0, VB0, EB0;
	// 创建所需要的对象
	GLCall(glGenVertexArrays(1, &VA0));
	GLCall(glGenBuffers(1, &VB0));
	GLCall(glGenBuffers(1, &EB0));

	// 将 vertex buffer 中的数据，传输到 GPU
	GLCall(glBindVertexArray(VA0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VB0));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices[0], GL_STATIC_DRAW));
	std::cout << u8"数据大小： " << sizeof(m_vertices) << std::endl;
	// 将 indices 传话传输到 GPU
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EB0));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices[0], GL_STATIC_DRAW));

	// 设置顶点坐标指针
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));

	// 设置法线坐标
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)));

	// 设置纹理坐标
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords)));

	GLCall(glBindVertexArray(0));



	// Render
	Render* rdPtr = new Render();
	Shader* shaderPtr = new Shader("shader/model/vertex.shader", "shader/model/fragment.shader");


	//std::string path = "res/model/beidou/beidou.pmx";
	std::string path = "D:/workdir/elden_ring/map_unpack/stormveil/m10_00_00_00_910014.smd";

	//std::string path = "res/model/c2010.fbx";
	//std::string path = "res/model/cube.obj";
	Model3D model3D(path);
	std::cout <<u8"model 节点数量：" << model3D.meshes.size() << std::endl;

	std::cout << u8"vertex 数量：" << model3D.meshes[0].m_vertices.size() << std::endl;

	std::cout << u8"texture 信息" <<model3D.existTextures.size()<< std::endl;
	for (auto ele : model3D.existTextures) {
		int st = ele.first.find_last_of('/');
		std::string subs = ele.first.substr(st + 1);
		std::cout << subs << ": ";
		for (auto c : subs) {
			int tmpC = (uint8_t)c;
			std::cout << tmpC << " ";
		}
		std::cout <<  std::endl;
	}

	std::string imgName = "res/Texture/container.jpg";
	Texture tex1 = Texture(imgName);


	while (!glfwWindowShouldClose(window))
	{
		camera.updateCamera(window);
		rdPtr->Clear();
		shaderPtr->Use();

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		GLCall(glActiveTexture(GL_TEXTURE0));
		tex1.Bind2D();
		GLCall(glUniform1i(glGetUniformLocation(shaderPtr->m_shaderProgramId, "outTexture1"), 0));

		

		glm::mat4 view = camera.getView();
		glm::mat4 projection = camera.getProjection(window);
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene

		shaderPtr->SetUniformMat4(model, "model");
		shaderPtr->SetUniformMat4(view, "view");
		shaderPtr->SetUniformMat4(projection, "projection");

		//model3D.Draw(*shaderPtr);
		glBindVertexArray(VA0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EB0);
		GLCall(glDrawElements(GL_TRIANGLES, sizeof(m_indices) / sizeof(m_indices[0]), GL_UNSIGNED_INT, nullptr));

		model3D.Draw(*shaderPtr);

		glfwSwapBuffers(window);
		// poll for and process events
		glfwPollEvents();
	}

	delete(shaderPtr);
	glfwTerminate();

	return 0;
}

#endif // 0