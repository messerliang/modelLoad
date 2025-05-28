#if 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include "GL_Error.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "constants.h"


int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}
	
	// 配置使用的版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "light scene", nullptr, nullptr);
	if (!window) {
		std::cerr << "window create failed\n"; 
		glfwTerminate();
		return -1;
	}

	camera.bindCallbackToWindow(window);
	

	// 讲指定窗口的上下文设置为当前线程的上下文
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;


	// 初始化 GLEW（必须在上下文创建后）
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}

	float cubePositions[] = {
		// 前面四个点
		-0.5f, -0.5f, 0.5f,
		 0.5f,  0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,

		// 后面四个点
		-0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
	};
	unsigned int cubeIndex[] = {
		// 前面
		0, 1, 2,
		0, 1, 3,

		// 后面
		4, 5, 6,
		4, 5, 7,

		//// 左
		0, 7, 4,
		0, 7, 3,

		// 右
		2, 5, 6, 
		2, 5, 1,

		// 上
		3, 5, 1, 
		3, 5, 7,

		// 下
		0, 6, 2,
		0, 6, 4,
	};

	VertexBuffer* vbPtr = new VertexBuffer(cubePositions, sizeof(cubePositions));
	vbPtr->Push<float>(3, false);

	IndexBuffer idxObj(cubeIndex, sizeof(cubeIndex)/sizeof(cubeIndex[0]));

	VertexArray* vaPtr = new VertexArray(*vbPtr, idxObj);
	

	Shader* cubeShader = new Shader("shader/light/basic.vert", "shader/light/basic.frag");

	// model、view、projection三件套
	glm::mat4 model(1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0), glm:: vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f * 800 / 600, 0.1f, 100.f);


	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		camera.updateCamera(window);

		// render here
		GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		cubeShader->Use();
		GLCall(glEnable(GL_DEPTH_TEST));

		view = camera.getView();
		projection = camera.getProjection(window);

		cubeShader->SetUniformMat4(model, "model");
		cubeShader->SetUniformMat4(view, "view");
		cubeShader->SetUniformMat4(projection, "projection");

		vaPtr->DrawElement(*cubeShader);


		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	delete(vaPtr);
	delete(vbPtr);
	delete(cubeShader);


	glfwDestroyWindow(window);
	glfwTerminate();
}


#endif