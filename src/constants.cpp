
#include <iostream>


#include "constants.h"
#include "Camera.h"


int screenWidth{ 800 }, screenHeight{ 800 };

//    bool keys[1024] = { false };
//    bool mouseKeys[1024] = { false };
//    
//    // �������صĲ���
//    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//    glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
//    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//    
//    // �������ת��صĲ�������λΪ��
//    float viewPitch = 0.0f;
//    float viewYaw = 0.0f;
//    
//    // ���λ��
//    bool resetMousePos = true;
//    double mouseX = screenWidth / 2.0f;
//    double mouseY = screenHeight / 2.0f;
//    
//    // ��֡������ص�����
//    float deltaTime = 0.0f;
//    float lastFrame = 0.0f;
//    
//    // ��������
//    float fov = 60.0f;

Camera camera;
