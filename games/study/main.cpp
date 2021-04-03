#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>


uint32_t shaderProgram() {

}
uint32_t createVertexData(uint32_t* VBO) {

	float vertex[6] = { // POSITIONS
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		-0.5f,  0.5f
	};


	//uint32_t VAO;            // Vertex Array Object
	glGenBuffers(1, VBO); 	 // Se genera el buffer para el objetp

	//glBindVertexArray(VAO);   // se bindea el VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	std::cout << "size of vertex    : " << sizeof(vertex) << std::endl;
	std::cout << "size of float     : " << sizeof(float) << std::endl;
	std::cout << "size of 6 * float : " << 6 * sizeof(float) << std::endl;

	
   //glEnableVertexAttribArray(0);
	
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   //glBindVertexArray(0);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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

	/*******************************************
	 * SET WINDOW & OPENGL CONTEXT RENDER  end * 
	 *******************************************/

	
	uint32_t VBO;

	std::cout << "VBO antes " << VBO << std::endl;

	const uint32_t VAO = createVertexData(&VBO);

	std::cout << "VBO despues " << VBO << std::endl;


		

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