#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




class Camera
{
private:
	GLFWwindow* m_window;

	// �������صĲ���
	glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


	glm::vec3 m_cameraTarget = glm::vec3(0.0, 0.0, 0.0);

	// ������ƶ��ٶ�
	float m_speed = 3.0f;

	// �������ת��صĲ�������λΪ��
	float m_viewPitch = 0.0f;
	float m_viewYaw = 0.0f;

	// ���λ��
	bool m_resetMousePos = true;
	double m_mouseX = 0.0f;
	double m_mouseY =  0.0f;

	// �����ת
	bool m_startRotateFlag = false;
	bool m_updateRotateFlag = false;
	float m_rotateAnchorX = 0.0f;
	float m_rotateAnchorY = 0.0f;

	// ��֡������ص�����
	float m_deltaTime = 0.0f;
	float m_lastFrame = 0.0f;

	// ��������
	float m_fov = 30.0f;

	/// <summary>
	/// ���ͼ��̼�¼
	/// </summary>
	bool m_keys[1024] = { false };
	bool m_mouseKeys[1024] = { false };

	// ������ʾ�Ĳ���


public:
	Camera();


	void bindCallbackToWindow(GLFWwindow* window);
	void updateCamera(GLFWwindow* window);

	// ���ݸ����Ǹ����������ָ��
	void updateCameraDirection();
	void updateCameraPosition();
	void updateCameraRotation(GLFWwindow* window);

	glm::mat4 getView();
	glm::mat4 getProjection(GLFWwindow* window);

	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	
};

