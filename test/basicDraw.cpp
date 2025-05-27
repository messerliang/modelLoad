#if 0


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "GL_Error.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Render.h"
#include "Texture.h"
#include "Camera.h"
#include "Model3D.h"


#include "stb_image.h"






int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // ����ʹ�õİ汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }


    camera.bindCallbackToWindow(window);

    glfwMakeContextCurrent(window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;

    // ���ô�ֱͬ��
    // 0 ���� �رմ�ֱͬ����֡���ʿ������޸�
    // 1 ���� ������ֱͬ����ÿ����Ļˢ��ʱ�Ž���������
    // >1 ���� ��δ�ֱͬ�����ٽ���
    glfwSwapInterval(1);

    // ��ʼ�� GLEW�������������Ĵ�����
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // ��� OpenGL �汾
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";


    float positions[] = {
        // λ��             // û�� RBG ��ɫ  // ��������
        // ��
        -0.5f, -0.5f, -0.5f, 0.1f, 0.1f, 0.2f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.7f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.3f, 0.8f, 0.6f, 0.0f, 1.0f,

        // ��
        -0.5f, -0.5f, 0.5f, 0.1f, 0.1f, 0.2f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 0.7f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.5f, 0.3f, 0.8f, 0.6f, 0.0f, 1.0f,

        // ��
        -0.5f, -0.5f,  -0.5f, 0.1f, 0.1f, 0.2f, 0.0f, 0.0f,
        -0.5f,  0.5f,   0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
        -0.5f, -0.5f,   0.5f, 0.7f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  -0.5f, 0.3f, 0.8f, 0.6f, 0.0f, 1.0f,

        // ��
        0.5f, -0.5f,  -0.5f, 0.1f, 0.1f, 0.2f, 0.0f, 0.0f,
        0.5f,  0.5f,   0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
        0.5f, -0.5f,   0.5f, 0.7f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 0.3f, 0.8f, 0.6f, 0.0f, 1.0f,

        // ��
        -0.5f, 0.5f, -0.5f, 0.1f, 0.1f, 0.2f, 0.0f, 0.0f,
         0.5f, 0.5f,  0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 0.7f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f, 0.3f, 0.8f, 0.6f, 0.0f, 1.0f,

        // ��
        -0.5f, -0.5f, -0.5f, 0.1f, 0.1f, 0.2f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.7f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.3f, 0.8f, 0.6f, 0.0f, 1.0f,


    };


    unsigned int indices[] = {
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


    VertexBuffer* vbObj = new VertexBuffer(positions, sizeof(positions));
    vbObj->Push<float>(3, false);   // λ�� ��Ϣ
    vbObj->Push<float>(3, false);   // RGB ��Ϣ
    vbObj->Push<float>(2, false);   // ����ӳ�� ��Ϣ


    IndexBuffer* ibObj = new IndexBuffer(indices, sizeof(indices) / sizeof(indices[0]));

    VertexArray* vaObj = new VertexArray();
    vaObj->AddBuffer(*vbObj);


    float colorRed = 0.1f;
    float timeValue = 0.0f;

    Shader* shaderPtr = new Shader("shader/vertex.shader", "shader/fragment.shader");
    shaderPtr->Use();

    // ��������
    std::string imgName = "res/Texture/container.jpg";
    Texture tex1 = Texture(imgName);

    std::string pngName = "res/Texture/tmp.png";
    Texture tex2(pngName);

    // �任����
    glm::mat4 model(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // ���ù۲����
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // ����ͶӰ����
    glm::mat4 projection(1.0f);


    // Render
    Render* rdPtr = new Render();

    // ����ģ��
    std::string path = "res/model/beidou/beidou.pmx";
    Model3D beidou(path);

    // ȡ�����еİ�
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    while (!glfwWindowShouldClose(window)) {

        camera.updateCamera(window);

        /*do_movement();
        adjustDirection(window);*/


        rdPtr->Clear();
        shaderPtr->Use();
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLCall(glActiveTexture(GL_TEXTURE0));
        tex1.Bind2D();
        GLCall(glUniform1i(glGetUniformLocation(shaderPtr->m_shaderProgramId, "outTexture1"), 0));

        GLCall(glActiveTexture(GL_TEXTURE1));
        tex2.Bind2D();
        GLCall(glUniform1i(glGetUniformLocation(shaderPtr->m_shaderProgramId, "outTexture2"), 1));

        // �任����
        glm::mat4 trans(1.0f), stayStill(1.0f);


        view = camera.getView();
        projection = camera.getProjection(window);

        shaderPtr->SetUniformMat4(model, "model");
        shaderPtr->SetUniformMat4(view, "view");
        shaderPtr->SetUniformMat4(projection, "projection");



        for (int i = 0; i < 10; ++i) {

            glm::mat4 tmpModel(1.0f);
            tmpModel = glm::translate(tmpModel, cubePositions[i]);
            float angle = 20.0f * i + glfwGetTime() * 3;
            tmpModel = glm::rotate(tmpModel, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            shaderPtr->SetUniformMat4(tmpModel, "model");
            rdPtr->Draw(*vaObj, *ibObj, *shaderPtr);
        }
        model = glm::mat4(1.0f);
        shaderPtr->SetUniformMat4(model, "model");
        tex2.UnBind2D();
        beidou.Draw(*shaderPtr);

        glfwSwapBuffers(window);
        // poll for and process events
        glfwPollEvents();
    }
    delete(ibObj);
    delete(vbObj);
    delete(vaObj);
    delete(shaderPtr);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


#endif // 0