#include "Camera.h"

#include "Callback.h"

#include <iostream>


Camera::Camera(){}


void Camera::updateCameraDirection(){
    float distance = glm::distance(m_cameraPos, m_cameraTarget);

    double directX = distance * std::cos(glm::radians(m_viewPitch)) * std::sin(glm::radians(m_viewYaw));
    double directY = distance * std::sin(glm::radians(m_viewPitch));
    double directZ = distance * std::cos(glm::radians(m_viewPitch)) * std::cos(glm::radians(m_viewYaw));

    m_cameraDirection = glm::vec3(-directX, -directY, -directZ);
    m_cameraPos = m_cameraTarget - m_cameraDirection;

    glm::normalize(m_cameraDirection);

}

void Camera::updateCameraRotation(GLFWwindow* window) {
    static float tmpPitch = 0.0f;
    static float tmpYaw = 0.0f;
    double sensitivity = 0.1;
    if (m_mouseKeys[GLFW_MOUSE_BUTTON_LEFT]) {
        double xpos, ypos;
        int width, height;
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetFramebufferSize(window, &width, &height);
        ypos = height - ypos;

        if (m_startRotateFlag) {
            m_rotateAnchorX = xpos;
            m_rotateAnchorY = ypos;
            m_startRotateFlag = false;
            //std::cout << "set ancor��" << ypos << " " << m_rotateAnchorY << std::endl;

        }
        std::cout << "target: " << m_cameraTarget.x << ", " << m_cameraTarget.y << ", " << m_cameraTarget.z << std::endl;
        std::cout << "pos: " << m_cameraPos.x << ", " << m_cameraPos.y << ", " << m_cameraPos.z << std::endl;
        //std::cout << "Mouse clicked at: " << xpos << ", " << ypos << std::endl;
        float diffPitch = sensitivity * (m_rotateAnchorY - ypos);
        float diffYaw = sensitivity * (m_rotateAnchorX - xpos);
        tmpPitch = m_viewPitch + diffPitch;
        tmpYaw = m_viewYaw + diffYaw;



        if (tmpPitch > 89.9f) {
            tmpPitch = 89.9f;
        }
        else if (tmpPitch < -89.9f) {
            tmpPitch = -89.9f;
        }
        float distance = glm::distance(m_cameraPos, m_cameraTarget);

        double directX = distance * std::cos(glm::radians(tmpPitch)) * std::sin(glm::radians(tmpYaw));
        double directY = distance * std::sin(glm::radians(tmpPitch));
        double directZ = distance * std::cos(glm::radians(tmpPitch)) * std::cos(glm::radians(tmpYaw));

        m_cameraDirection = glm::vec3(-directX, -directY, -directZ);
        m_cameraPos = m_cameraTarget - m_cameraDirection;

        glm::normalize(m_cameraDirection);


        std::cout << "pitch: " << m_viewPitch << ", yaw: " << m_viewYaw << std::endl;
    }

    if (m_updateRotateFlag) {
        m_updateRotateFlag = false;
        m_viewPitch = tmpPitch;
        m_viewYaw = tmpYaw;

    }


}

void Camera::updateCameraPosition(){

    // ����ʱ��
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    float maxCameraSpeedFactor = 3.0f, minCameraSpeedFactor=0.5f;
    float multiply = 10.0f;

    if (m_keys[GLFW_KEY_LEFT_SHIFT]) {
        
        if (m_speed > minCameraSpeedFactor) {
            m_speed -= maxCameraSpeedFactor * multiply * m_deltaTime;
        }
        else if (m_speed < minCameraSpeedFactor) {
            m_speed = minCameraSpeedFactor;
        }
        
    }
    else {
        if (m_speed < maxCameraSpeedFactor) {
            m_speed += maxCameraSpeedFactor * multiply * m_deltaTime;
        }
    }

    GLfloat cameraSpeed = m_speed * m_deltaTime;
    // 
    // �����������ָ��ǰ���ƶ�
    glm::vec3 diff = 0.5f * cameraSpeed * m_cameraDirection;
    if (m_keys[GLFW_KEY_W]) {
        m_cameraPos += diff;
        //m_cameraTarget += diff;
    }
    if (m_keys[GLFW_KEY_S]) {
        m_cameraPos -= diff;
        //m_cameraTarget -= diff;
    }

    // ����������ƶ���x�᷽���ȸ�������������������򣬼���������
    diff = glm::normalize(glm::cross(m_cameraDirection, m_cameraUp)) * cameraSpeed;

    if (m_keys[GLFW_KEY_A]) {
        m_cameraPos += diff;
        m_cameraTarget += diff;

    }
    if (m_keys[GLFW_KEY_D]) {
        m_cameraPos -= diff;
        m_cameraTarget -= diff;
    }
    // ����������ƶ�
    diff = m_cameraUp * cameraSpeed;
    if (m_keys[GLFW_KEY_Q]) {
        m_cameraPos += diff;
        m_cameraTarget += diff;
    }
    if (m_keys[GLFW_KEY_E]) {
        m_cameraPos -= diff;
        m_cameraTarget -= diff;
    }
    
}



void Camera::bindCallbackToWindow(GLFWwindow* window) {
    // ���ü��̻ص�����
    glfwSetKeyCallback(window, key_callback);
    // ����������ص�����
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // �����������¼�
    glfwSetScrollCallback(window, mouse_scroll_callback);

    // ע�ᴰ�ڱ仯ʱ��Ļص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Camera::updateCamera(GLFWwindow* window) {
    updateCameraPosition();
    updateCameraRotation(window);
}


glm::mat4 Camera::getView() {
    // lookat �������������������
    // ��һ�������λ��
    // �ڶ�����Ŀ��λ��
    // �������������������

    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraDirection, m_cameraUp);
}

glm::mat4 Camera::getProjection(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    return glm::perspective(glm::radians(m_fov), 1.0f * width / height, 0.1f, 100.f);
}

glm::vec3 Camera::getPosition() const {
    return m_cameraPos;
}
