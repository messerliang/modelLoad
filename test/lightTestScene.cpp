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
#include "Texture.h"


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
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
	vbPtr->Push<float>(3, false);
	vbPtr->Push<float>(2, false);

	IndexBuffer idxObj(cubeIndex, sizeof(cubeIndex)/sizeof(cubeIndex[0]));

	VertexArray* vaPtr = new VertexArray(*vbPtr, idxObj);
	

	Shader* cubeShader = new Shader("shader/light/Phong.vert", "shader/light/Phong.frag");
	Shader* lightShader = new Shader("shader/light/light.vert", "shader/light/light.frag");

	// ��������
	Texture tex0("res/Texture/container2.png");
	Texture texSpec("res/Texture/container2_specular.png");

	// model��view��projection������
	glm::mat4 model(1.0f);
	glm::mat4 view =camera.getView();
	glm::mat4 projection = camera.getProjection(window);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::mat4 lightModel(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f), objectColor(1.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		camera.updateCamera(window);

		// render here
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		// ������Ȳ���
		glEnable(GL_DEPTH_TEST);

		cubeShader->Use(); 

		view = camera.getView();
		projection = camera.getProjection(window);

		cubeShader->SetUniformMat4(model, "model");
		cubeShader->SetUniformMat4(view, "view");
		cubeShader->SetUniformMat4(projection, "projection");


		cubeShader->SetUniformV3(lightPos, "lightPos");
		cubeShader->SetUniformV3(lightColor, "lightColor");
		cubeShader->SetUniformV3(camera.getPosition(), "viewPos");

		/*GLCall(glActiveTexture(GL_TEXTURE0));
		tex0.Bind2D();
		GLCall(glUniform1i(glGetUniformLocation(cubeShader->m_shaderProgramId, "materialTex.diffuse"), 0));*/
		cubeShader->SetTexture(tex0, GL_TEXTURE0, "materialTex.diffuse");
		cubeShader->SetTexture(texSpec, GL_TEXTURE1, "materialTex.specular");
		// ��������ķ���
		//cubeShader->SetUniformV3(glm::vec3(1.0f, 0.5f, 0.31f), "materialTex.ambient");
		//cubeShader->SetUniformV3(glm::vec3(1.0f, 0.5f, 0.31f), "material.diffuse");
		cubeShader->SetUniformV3(glm::vec3(0.5f, 0.5f, 0.5f), "materialTex.specular");
		cubeShader->SetUniform1f(32.0f, "materialTex.shiness");
		// ��������������Ȼ����⡢�����䡢���淴���ǿ��
		cubeShader->SetUniformV3(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient"); // �������ǿ�ȱȽ����������������ñȽ�С��ֵ
		cubeShader->SetUniformV3(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse");
		cubeShader->SetUniformV3(glm::vec3(1.0f, 1.0f, 1.0f), "light.specular");
		//cubeShader->SetUniform1f(0.5f, "specularStrength");

		vaPtr->DrawArray(*cubeShader);


		// ���ƹ�Դ
		lightShader->Use();
		lightShader->SetUniformMat4(lightModel, "model");
		lightShader->SetUniformMat4(view, "view");
		lightShader->SetUniformMat4(projection, "projection");
		vaPtr->DrawArray(*lightShader);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	delete(vaPtr);
	delete(vbPtr);
	delete(cubeShader);
	delete(lightShader);


	glfwDestroyWindow(window);
	glfwTerminate();
}


#endif