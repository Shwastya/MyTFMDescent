#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
void render(uint32_t VAO, uint32_t program) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
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

bool checkProgram(uint32_t program) {

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Error Linking Program " << infoLog << std::endl;
        return false;
    }
    return true;
}






std::string createGLSL(uint32_t type)
{
	switch (type)
	{
		case GL_VERTEX_SHADER:
		
			return 
			"#version 330 core\n"
			"layout (location=0) in vec3 aPos;\n"
			"void main() {\n"
			"    gl_Position = vec4(aPos, 1.0);\n"
			"}\0";
			break;	
			
		case GL_FRAGMENT_SHADER:
			return
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main() {\n"
			"    FragColor = vec4(0.6, 0.6, 0.1, 1.0);\n"
			"}\0";
			break;
		default:
		return "failed";
		break;
	}
}
/* 2 a */
static uint32_t compileShader(uint32_t type, const std::string& source) {

	const uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// error handling
	const bool check = checkShader(id, GL_VERTEX_SHADER);

	if (!check) glDeleteShader(id);
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
/* 1. */
/* uint32_t createVertexData(uint32_t* VBO) {

	float vertex[6] = { // POSITIONS
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		-0.5f,  0.5f
	};


	//uint32_t VAO;            // Vertex Array Object
	glGenBuffers(1, VBO); 	 // Se genera el buffer para el objetp

	//glBindVertexArray(VAO);   // se bindea el VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);  // se bindean los objetos de vertices
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW); // se suben a la GPU

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0); // puntero en el espacio
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // puntero en el espacio


	std::string vertexShader   = createGLSL(GL_VERTEX_SHADER);
	std::string fragmentShader = createGLSL(GL_FRAGMENT_SHADER);

	uint32_t shader = createShader(vertexShader, fragmentShader);
	glUseProgram(shader);
	
   // glEnableVertexAttribArray(0); // VAO enable
	
   // glBindBuffer(GL_ARRAY_BUFFER, 0);

   //glBindVertexArray(0);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return shader;

}
 */
int main(int, char* []) {

	/*******************************************
	 * SET WINDOW & OPENGL CONTEXT RENDER init * 
	 *******************************************/
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
	/* Bacground Color */
	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

	/* Show VERSION */
	std::cout << glGetString(GL_VERSION) << std::endl;

	

	
	/* 1. create VBO and VAO */
	// uint32_t VBO; 
	// const uint32_t VAO = createVertexData(&VBO); 


	float vertex[6] = { // POSITIONS
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};


	uint32_t VBO;
	//uint32_t VAO;            // Vertex Array Object
	glGenBuffers(1, &VBO); 	 // Se genera el buffer para el objetp

	//glBindVertexArray(VAO);   // se bindea el VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);  // se bindean los objetos de vertices
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW); // se suben a la GPU

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0); // puntero en el espacio
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // puntero en el espacio


	std::string vertexShader   = 
			"#version 330 core\n"
			"layout (location=0) in vec3 aPos;\n"
			"void main() {\n"
			"    gl_Position = vec4(aPos, 1.0);\n"
			"}\0";
	std::string fragmentShader = 
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main() {\n"
			"    FragColor = vec4(0.6, 0.6, 0.1, 1.0);\n"
			"}\0";

	uint32_t shader = createShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	//const uint32_t program = createShader();



		

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		/******************/
		/* code to render */
		/******************/
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}