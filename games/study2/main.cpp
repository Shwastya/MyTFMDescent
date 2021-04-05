#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>





bool checkShader(uint32_t id, uint32_t type)
{
    int success;  
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) 
	 {

		  int length;
		  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		  /* allocate memory to avoid memory leak */
		  char* infolog = static_cast<char*>(alloca(length * sizeof(char)));

        glGetShaderInfoLog(id, length, &length, infolog);
        std::cout << "Failed to compile " << 
		  	(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		  std::cout << infolog << std::endl;
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




/* 2 a */
static uint32_t compileShader(uint32_t type, const std::string& source) {

	const uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// error handling
	checkShader(id, GL_VERTEX_SHADER);

	//if (!check) glDeleteShader(id);
	return id;
}

/* 2 */
static uint32_t createShader(const std::string& vs, const std::string& fs) {

	uint32_t program = glCreateProgram();
	uint32_t _vs = compileShader(GL_VERTEX_SHADER, vs);
	uint32_t _fs = compileShader(GL_FRAGMENT_SHADER, fs);

	glAttachShader(program, _vs);
	glAttachShader(program, _fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(_vs);
	glDeleteShader(_fs);

	return program;

}

int main(int, char* []) {

	
	/* Initialize the library */
	if (!glfwInit()) {
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


	/* Initialize glad */ /// ever!! after opengl contextCurrent
	if (!gladLoadGL()) {
        std::cout << "Error Initializing GLAD" << std::endl;
        glfwTerminate();
        return -1;
   }
	
	

	/* Show VERSION */
	std::cout << glGetString(GL_VERSION) << std::endl;

	



	float vertex[] = {
        -0.5f, -0.5f,    
        0.5f, -0.5f,   
        0.5f, 0.5f,

		  


    };

    uint32_t indices[] = {
        0, 2, 1
    };




	uint32_t VBO, EBO, VAO;	         
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); 	 // Se genera el buffer VBO
//	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);   // se bindea el VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);  // se bindean los objetos de vertices
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW); // se suben a la GPU

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0); // puntero en el espacio
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glEnableVertexAttribArray(0);
   //glBindVertexArray(0);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* PROGRAM */	

	ShaderProgramSources source = ParseShader("../assets/shaders/basic.shader");

	uint32_t shader = createShader(source.vertexSource, source.fragmentSource);
	glUseProgram(shader);
	//glBindVertexArray(VAO);

	/* somo SETS   */
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK); 

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		/******************/
		/* code to render */
		/******************/
		glDrawArrays(GL_TRIANGLES, 0, 3);		
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		/******************/
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);

   glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}