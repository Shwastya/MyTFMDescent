#include "engine/system/render.hpp"



namespace TFM_ECS {

	RenderSystem_t::RenderSystem_t(const uint32_t w, const uint32_t h, const char* t)
	: _width { w }, _height { h }, _title { t }
	{		
		if (!glfwInit()) {
			std::cout << "Error Initializing GLFW" << std::endl;
			exit(-1);
    	}
		 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		 _window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
		 
		 if (!_window) {
			 std::cout << "Error Creating Window" << std::endl;
			 glfwTerminate();
			 exit(-1);
		}
		
		glfwMakeContextCurrent(_window);
		glfwSwapInterval(1); // Enable vsync
		
		if (!gladLoadGL()) {
        std::cout << "Error Initializing GLAD" << std::endl;
        exit(-1);
		}
		
		//glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	RenderSystem_t::~RenderSystem_t() { glfwTerminate(); }

	uint32_t RenderSystem_t::getWidth()  const { return _width;  };
	uint32_t RenderSystem_t::getHeight() const { return _height; };

	void RenderSystem_t::update() const {

		while (RenderSystem_t::alive())
		{
			glClear(GL_COLOR_BUFFER_BIT);
			RenderSystem_t::frame();
		}
	}

	bool RenderSystem_t::alive() const {
		return !glfwWindowShouldClose(_window);
	}

	void RenderSystem_t::frame() const {
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

} // namespace TFM_ECS