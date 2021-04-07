#include "engine/object/vao.hpp"

namespace TFM_ECS {

vao_t::vao_t() 
{
	GLHE_(glGenVertexArrays(1, &_VAO_ID));
	// GLHE_(glBindVertexArray(_VAO_ID)); 

}

vao_t::~vao_t()
{

	GLHE_(glDeleteVertexArrays(1, &_VAO_ID));
}

void vao_t::addBuffer(const vbo_t& VBO, const vbl_t& VBLayout) 
{
	bind(); // bind VAO
	VBO.bind();
	const auto& elements = VBLayout.getElements();


	uint32_t ofsset = 0;

	std::cout << "elements size: " << elements.size() << std::endl;

	for (uint32_t i = 0; i < elements.size(); i++) 
	{
		const auto& e = elements[i];
		GLHE_(glEnableVertexAttribArray(i));
    //GLHE_(glVertexAttribPointer(0, 2      , GL_FLOAT, GL_FALSE   , sizeof(float) * 2   , (void*)0));
		glVertexAttribPointer(i, e.count, e.type, e.normalized , VBLayout.getStride(), (const void*)(uintptr_t)ofsset);

		std::cout << "ofset at index i " << i << ": " << ofsset << std::endl;

		ofsset += e.count * vbe_t::getSizeOfType(e.type);

		
	
	}	
}
void vao_t::bind() const
{
	GLHE_(glBindVertexArray(_VAO_ID));
}
void vao_t::unbind() const
{
	GLHE_(glBindVertexArray(0));
}}