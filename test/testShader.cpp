
#if 0

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>


#include "Shader.h"
#include "constants.h"
#include "GL_Error.h"
#include "Model3D.h"


int main() {
	std::cout << "hello\n";
	glfwInit();

	// 配置使用的版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "shaderTest", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	// 初始化 GLEW（必须在上下文创建后）
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}
	Shader* shader = new Shader("shader/testGLSL/vert.shader", "shader/testGLSL/frag.shader");
	shader->Use();

	float vertices[] = {
		// positions       // texcoords (optional)
		 1.0f,  1.0f,  0.0f,      // top right
		 1.0f, -1.0f,  0.0f,      // bottom right
		-1.0f, -1.0f,  0.0f,      // bottom left
		-1.0f,  1.0f,  0.0f,      // top left
	};

	unsigned int indices[] = {
		0,1,2,
		0,2,3,
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	// 添加一个三角形
	float triangleVertices[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};
	GLuint triVAO, triVBO;
	glGenVertexArrays(1, &triVAO);
	glGenBuffers(1, &triVBO);
	glBindVertexArray(triVAO);
	glBindBuffer(GL_ARRAY_BUFFER, triVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader* triangleShader = new Shader("shader/triangle.vert", "shader/triangle.frag");


	while (!glfwWindowShouldClose(window)) {
		// Define the viewport dimensions
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader->Use();
		shader->SetUniform1f(glfwGetTime(), "curTime");
		shader->SetUniform1f(glfwGetTime(), "iTime");

		glm::vec3 resolution = glm::vec3(width, height, 1.0);
		shader->SetUniformV3(resolution, "iResolution");
		//std::cout << "cur time: " << glfwGetTime() << std::endl;
		

		GLCall(glBindVertexArray(VAO));
		GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0));


		// 绘制三角形
		triangleShader->Use();
		glBindVertexArray(triVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);




		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}



#endif