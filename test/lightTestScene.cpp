#if 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include "GL_Error.h"

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

	// 
	glfwMakeContextCurrent(window);
}


#endif