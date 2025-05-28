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
	
	// ����ʹ�õİ汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	// ��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "light scene", nullptr, nullptr);
	if (!window) {
		std::cerr << "window create failed\n"; 
		glfwTerminate();
		return -1;
	}

	camera.bindCallbackToWindow(window);
	

	// ��ָ�����ڵ�����������Ϊ��ǰ�̵߳�������
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;


	// ��ʼ�� GLEW�������������Ĵ�����
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}

	float cubePositions[] = {
		// ǰ���ĸ���
		-0.5f, -0.5f, 0.5f,
		 0.5f,  0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,

		// �����ĸ���
		-0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
	};
	unsigned int cubeIndex[] = {
		// ǰ��
		0, 1, 2,
		0, 1, 3,

		// ����
		4, 5, 6,
		4, 5, 7,

		//// ��
		0, 7, 4,
		0, 7, 3,

		// ��
		2, 5, 6, 
		2, 5, 1,

		// ��
		3, 5, 1, 
		3, 5, 7,

		// ��
		0, 6, 2,
		0, 6, 4,
	};

	VertexBuffer* vbPtr = new VertexBuffer(cubePositions, sizeof(cubePositions));
	vbPtr->Push<float>(3, false);

	IndexBuffer idxObj(cubeIndex, sizeof(cubeIndex)/sizeof(cubeIndex[0]));

	VertexArray* vaPtr = new VertexArray(*vbPtr, idxObj);
	

	Shader* cubeShader = new Shader("shader/light/basic.vert", "shader/light/basic.frag");

	// model��view��projection������
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