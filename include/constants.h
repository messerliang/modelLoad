#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Camera.h"

extern int screenWidth;
extern int screenHeight;

//     extern bool keys[1024];
//     extern bool mouseKeys[1024];
//     
//     // �������صĲ���
//     extern glm::vec3 cameraPos;
//     extern glm::vec3 cameraDirection;
//     extern glm::vec3 cameraUp;
//     
//     // �������ת��صĲ�������λΪ��
//     extern float viewPitch;
//     extern float viewYaw;
//     
//     // ���λ��
//     extern bool resetMousePos;
//     extern double mouseX;
//     extern double mouseY;
//     
//     // ��֡������ص�����
//     extern float deltaTime;
//     extern float lastFrame;
//     
//     
//     // ��������
//     extern float fov;

// ���������
extern Camera camera;