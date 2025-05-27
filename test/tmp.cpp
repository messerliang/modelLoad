
#if 0

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>


#include "Shader.h"
#include "constants.h"
#include "GL_Error.h"

int main() {
	std::cout << "hello\n";
	glfwInit();

	// ����ʹ�õİ汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "shaderTest", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	// ��ʼ�� GLEW�������������Ĵ�����
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}
	Shader* shader = new Shader("shader/testGLSL/vert.shader", "shader/testGLSL/frag.shader");
	shader->Use();
	// ���Ƶ�����
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
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glGenBuffers(1, &EBO));

	// vertex array
	GLCall(glBindVertexArray(VAO));

	// vertex buffer
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	// index buffer
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	// ���ö�����Ϣ������ֻ��һ��λ����Ϣ������ֻ����0����
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));


	// ��ʱ�ص� va �Ĺ���
	GLCall(glBindVertexArray(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader->Use();

		GLCall(glBindVertexArray(VAO));
		GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0));

		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}



#endif