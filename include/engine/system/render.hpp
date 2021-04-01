#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace TFM_ECS {

class RenderSystem_t {

	explicit RenderSystem_t() 
	{
		initglfw();

    	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   
    	initWindow();

    	glfwMakeContextCurrent(_window);

    	if (!gladLoadGL()) {
			 std::cout << "Error Initializing GLAD" << std::endl;
			 glfwTerminate();
			 //return -1;
    }

    glfwSetFramebufferSizeCallback(window, onChangeFrameBufferSize);

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    while(!glfwWindowShouldClose(_window)) {
		 
		 handleInput(_window);
		 
		 //render();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    glfwTerminate();
	}
	int initglfw() {
		if (!glfwInit()) {
        std::cout << "Error Initializing GLFW" << std::endl;
        return -1;
    }
	}
	 int initWindow() 
	 {
		 _window = glfwCreateWindow(_width, _height, "04MVID", nullptr, nullptr);
		 if (!_window) {
        std::cout << "Error Creating Window" << std::endl;
        glfwTerminate();
        return -1;
    }
	 }
	}
	private:

		GLFWwindow* _window;
		const uint32_t _width = 1920;
      const uint32_t _height = 1080;

};}