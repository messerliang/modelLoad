#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <random>

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


#if 1



int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // ����ʹ�õİ汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "WangDaMu", nullptr, nullptr);
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


    // ����Ǳ�������
    Shader* shaderBg = new Shader("shader/gyroid/vert.shader", "shader/gyroid/frag.shader");


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

   


    // ������ģ�ͼ�����صĲ���
    Shader* shaderModel = new Shader("shader/model/vertex.shader", "shader/model/fragment.shader");
    // �任����
    glm::mat4 model(1.0f);
    // ���ù۲����
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // ����ͶӰ����
    glm::mat4 projection(1.0f);

    


    // ����ģ��
    
    std::vector<std::string> modelPaths = {
        "res/model/beidou/beidou.pmx",
        "res/model/lanyan/lanyan.pmx",
        "res/model/nilu/nilu.pmx",
        "res/model/paimeng/paimeng.pmx",
        "res/model/qiliangliang/qiliangliang.pmx",
        "res/model/qiliangliang/qiliangliangTransform.pmx",
        "res/model/maweika/maweika.pmx",
        "res/model/maweika/helmat.pmx",
        "res/model/maweika/motor.pmx",
    };

    std::vector<Model3D> modelMihayo;
    std::vector<std::vector<float>> speedPhase;
    std::random_device rd;  // ��������ӣ�Ӳ����
    std::mt19937 gen(rd()); // ÷ɭ��ת����
    std::uniform_real_distribution<> speedDist(0.0f, 3.0f);
    std::uniform_real_distribution<> phaseDist(0.0f, 3.14f);
    for (const auto& path : modelPaths) {
        modelMihayo.emplace_back(path);
        float speed = speedDist(gen);
        float phase = phaseDist(gen);
        float dir = (rand() % 2 == 0) * 2 - 1;
        speedPhase.push_back({ speed, phase, dir });
    }



    // ȡ�����еİ�
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));



    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);


        camera.updateCamera(window);
        float curTime = glfwGetTime();
        

        /*GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLCall(glEnable(GL_DEPTH_TEST));*/
        // ÿ֡��ʼǰ
        GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ���Ʊ���
        glDisable(GL_DEPTH_TEST);
        shaderBg->Use();
        shaderBg->SetUniform1f(curTime, "curTime");
        shaderBg->SetUniform1f(curTime, "iTime");
        glm::vec3 resolution = glm::vec3(width, height, 1.0);
        shaderBg->SetUniformV3(resolution, "iResolution");
        GLCall(glBindVertexArray(VAO));
        GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0));



        // ������Ȳ���
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);



        view = camera.getView();
        projection = camera.getProjection(window);

        shaderModel->Use();
        
        //glm::mat4 m1 = glm::rotate(model, glm::radians(curTime *  5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //shaderModel->SetUniformMat4(m1, "model");
        //shaderModel->SetUniformMat4(view, "view");
        //shaderModel->SetUniformMat4(projection, "projection");
        //beidou.Draw(*shaderModel);


        //glm::mat4 modelTrans = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));

        //shaderModel->SetUniformMat4(modelTrans, "model");
        //lanyan.Draw(*shaderModel);

        for (int i = 0; i < modelMihayo.size(); ++i) {
            float transX = i * 15.0f;
            glm::mat4 m = glm::translate(model, glm::vec3(transX, 0.0f, 0.0f));
            float dir = speedPhase[i][2];
            m = glm::rotate(m, dir*glm::radians(curTime * (speedPhase[i][0] + 12)) + speedPhase[i][1], glm::vec3(0.0f, 1.0f, 0.0f));
            
            shaderModel->SetUniformMat4(m, "model");
            shaderModel->SetUniformMat4(view, "view");
            shaderModel->SetUniformMat4(projection, "projection");
            modelMihayo[i].Draw(*shaderModel);
        }

       
        // һЩ�����صĲ���
        glfwSwapBuffers(window);
        // poll for and process events
        glfwPollEvents();
    }

    delete(shaderModel);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


#endif // 0