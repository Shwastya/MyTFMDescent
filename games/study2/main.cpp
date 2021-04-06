#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <cstdint>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _MSC_VER
	#define ASSERT(x) if (!(x)) __debugbreak()
#endif
#ifdef __linux__
	#include <signal.h>
	#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#endif

#define GLCALL(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))



static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);	
}
static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << 
		function  << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}



struct ShaderProgramSources {
	std::string vertexSource;
	std::string fragmentSource;
};

static ShaderProgramSources ParseShader(const std::string& filepath) 
{

	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find("Vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("Fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else 
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}




bool checkShader(uint32_t id, uint32_t type)
{
    int success;  
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (success == GL_FALSE) 
	 {

		  int length;
		  GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		  /* allocate memory to avoid memory leak */
		  char* infolog = static_cast<char*>(alloca(length * sizeof(char)));

        GLCALL(glGetShaderInfoLog(id, length, &length, infolog));
        std::cout << "Failed to compile " << 
		  	(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		  std::cout << infolog << std::endl;
		  GLCALL(glDeleteShader(id));
        return false;
    }
    return true;
}


static uint32_t compileShader(uint32_t type, const std::string& source) {

	const uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	GLCALL(glShaderSource(id, 1, &src, nullptr));
	GLCALL(glCompileShader(id));
	
	checkShader(id, GL_VERTEX_SHADER); // error handling

	return id;
}

static uint32_t createShader(const std::string& vs, const std::string& fs) {

	uint32_t program = glCreateProgram();
	uint32_t _vs = compileShader(GL_VERTEX_SHADER, vs);
	uint32_t _fs = compileShader(GL_FRAGMENT_SHADER, fs);

	GLCALL(glAttachShader(program, _vs));
	GLCALL(glAttachShader(program, _fs));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));

	GLCALL(glDeleteShader(_vs));
	GLCALL(glDeleteShader(_fs));

	return program;
}

int main(int, char* []) 
{
	if (!glfwInit()) 
	{
		std::cout << "Error Initializing GLFW" << std::endl;
		return -1;
	}

	/* Render context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 

	/* Profiles (perfiles)
	*  1. Fixed 
	*  2. Core
	*	3. 3.3 (actualmente 4.3) 
	*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpneGL context */
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}	
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	/* Initialize glad */ /// ever!! after opengl contextCurrent
	if (!gladLoadGL()) {
        std::cout << "Error Initializing GLAD" << std::endl;
        glfwTerminate();
        return -1;
   }
	/* Show VERSION */
	std::cout << glGetString(GL_VERSION) << std::endl;	



	float vertex[] = {
        -0.5f, -0.5f,  // 0  
        0.5f, -0.5f,   // 1
       // 0.5f, 0.5f,

		  0.5f, 0.5f,    // 2
		  -0.5f, 0.5f,   // 3
		 // -0.5f, -0.5f
    };

    uint32_t indices[] = {
        0, 1, 2,
		  2, 3, 0
    };

	uint32_t VAO;	         
	GLCALL(glGenVertexArrays(1, &VAO));
	GLCALL(glBindVertexArray(VAO)); 

	uint32_t VBO;	 
	GLCALL(glGenBuffers(1, &VBO));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
   GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0));
	
	uint32_t EBO;
	GLCALL(glGenBuffers(1, &EBO));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
   GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
	
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	
   GLCALL(glBindVertexArray(0));

   GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	GLCALL(glBindVertexArray(VAO));



	/* PROGRAM */	

	ShaderProgramSources source = ParseShader("../assets/shaders/basic.shader");
	uint32_t shader = createShader(source.vertexSource, source.fragmentSource);	
	GLCALL(glUseProgram(shader));	

	

	/* UNIFORMS */
	const int location = glGetUniformLocation(shader, "u_color");
	assert(location != 1);

	GLCALL(glUniform4f(location, 0.9f, 0.3f, 0.4f, 1.0f));
	
	



	/* some SETS   */
	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

   GLCALL(glEnable(GL_CULL_FACE));
   GLCALL(glCullFace(GL_BACK)); 

	//GLCALL(glClearColor(0.0f, 0.3f, 0.6f, 1.0f));


	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));


		const double timer { glfwGetTime() };
		const float R { static_cast<float>(abs(sin(timer))) };
		const float G { static_cast<float>(abs(sin(timer + M_PI / 2))) };
		const float B { static_cast<float>(abs(sin(timer + M_PI / 4))) };

		std::cout << "Red:   " << R << std::endl << "Blue:  " << B << std::endl << "Green: " << G << std::endl;

		GLCALL(glUniform4f(location, R, G, B, 1.0f));
		GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

   glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}