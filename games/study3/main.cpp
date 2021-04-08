#include <engine/system/handleGLerrors.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <fstream>
#include <string>
#include <sstream>

#include <cstdint>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>


#include "engine/object/vbo.hpp"
#include "engine/object/ebo.hpp"
#include "engine/object/vao.hpp"

using namespace TFM_ECS;

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
    GLHE_(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (success == GL_FALSE) 
	 {

		  int length;
		  GLHE_(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		  /* allocate memory to avoid memory leak */
		  char* infolog = static_cast<char*>(_malloca(length * sizeof(char)));

        GLHE_(glGetShaderInfoLog(id, length, &length, infolog));
        std::cout << "Failed to compile " << 
		  	(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		  std::cout << infolog << std::endl;
		  GLHE_(glDeleteShader(id));
        return false;
    }
    return true;
}


static uint32_t compileShader(uint32_t type, const std::string& source) 
{

	GLHE_(const uint32_t id = glCreateShader(type));
	const char* src = source.c_str();
	GLHE_(glShaderSource(id, 1, &src, nullptr));
	GLHE_(glCompileShader(id));
	
	checkShader(id, GL_VERTEX_SHADER); // error handling

	return id;
}

static uint32_t createShader(const std::string& vs, const std::string& fs) {

	GLHE_(uint32_t program = glCreateProgram());
	uint32_t _vs = compileShader(GL_VERTEX_SHADER, vs);
	uint32_t _fs = compileShader(GL_FRAGMENT_SHADER, fs);

	GLHE_(glAttachShader(program, _vs));
	GLHE_(glAttachShader(program, _fs));
	GLHE_(glLinkProgram(program));
	GLHE_(glValidateProgram(program));

	GLHE_(glDeleteShader(_vs));
	GLHE_(glDeleteShader(_fs));

	return program;
}

int main(int, char* []) 
{
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



	const float vertex[8] = {
        -0.5f, -0.5f,  // 0  
        0.5f, -0.5f,   // 1
       // 0.5f, 0.5f,

		  0.5f, 0.5f,    // 2
		  -0.5f, 0.5f,   // 3
		 // -0.5f, -0.5f
    };

	const glm::vec2 vertices[4] =
	{
		glm::vec2(-0.5f, -0.5f),
		glm::vec2( 0.5f, -0.5f),
		glm::vec2( 0.5f,  0.5f),
		glm::vec2(-0.5f,  0.5f)
	};

    uint32_t indices[6] = {
        0, 1, 2,
		  2, 3, 0
    };

	std::cout << "size of float vertex:      " << sizeof(vertex) << std::endl;
	std::cout << "size of vec2 float vertex: " << sizeof(vertices) << std::endl;
	//uint32_t VAO;	         
	//GLHE_(glGenVertexArrays(1, &VAO));
	//GLHE_(glBindVertexArray(VAO)); 

	vao_t VAO;	
	//vbo_t VBO(vertex, sizeof(vertex));
	vbo_t VBO;// (vertex, sizeof(vertex));
	VBO.setBufferObject(vertices, sizeof(vertices));
	vbl_t layout;
	layout.push<float>(2, "triangulo"); // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0)
	VAO.addBuffer(VBO, layout);  //VAO.AddBuffer(VBO);

	//BufferLayout layout;
	//layout.Push<float>(3);
	//VAO.addLayout(layout);


	/* GLHE_(glEnableVertexAttribArray(0));
	GLHE_(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0)); */


	ebo_t EBO(indices, sizeof(indices));
	
	
	/* PROGRAM */	

	ShaderProgramSources source = ParseShader("../assets/shaders/basic.shader");
	uint32_t shader = createShader(source.vertexSource, source.fragmentSource);	
	GLHE_(glUseProgram(shader));	


	/* UNIFORMS */
	GLHE_(const uint32_t location = glGetUniformLocation(shader, "u_color"));
	assert(location != 1);

	GLHE_(glUniform4f(location, 0.9f, 0.3f, 0.4f, 1.0f));
	
	
	/* UNBINDS */
	//GLHE_(glBindVertexArray(0));							 // unbind VAO
	VAO.unbind();
	GLHE_(glUseProgram(0));									 // unbind shader program
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, 0));			 // unbind VBO
	GLHE_(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // unbind EBO
	//VBO.unbind();
	//EBO.unbind();
	






	/* some SETS   */
	GLHE_(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

   GLHE_(glEnable(GL_CULL_FACE));
   GLHE_(glCullFace(GL_BACK)); 

	GLHE_(glClearColor(0.0f, 0.3f, 0.6f, 1.0f));


	double timer = 0.0;
	float R = 0.0f;
	float G = 0.0f;
	float B = 0.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		
		GLHE_(glClear(GL_COLOR_BUFFER_BIT));


		GLHE_(glUseProgram(shader));
		GLHE_(glUniform4f(location, R, G, B, 1.0f));	


		//GLHE_(glBindVertexArray(VAO));
		VAO.bind();
		EBO.bind();
		
		GLHE_(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		
		timer = glfwGetTime();
		R = static_cast<float>(abs(sin(timer)));
		G = static_cast<float>(abs(sin(timer + M_PI / 2)));
		B = static_cast<float>(abs(sin(timer + M_PI / 4)));



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//GLHE_(glDeleteVertexArrays(1, &VAO));
/*    GLHE_(glDeleteBuffers(1, &VBO));
	GLHE_(glDeleteBuffers(1, &EBO)); */

   GLHE_(glDeleteProgram(shader));
	}
	glfwTerminate();
	return 0;
}