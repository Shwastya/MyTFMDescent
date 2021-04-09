#include "engine/object/vbo.hpp"
#include "engine/system/handleGLerrors.hpp"


namespace TFM_ECS {


vbo_t::vbo_t(const void* data, const uint32_t nVertices) // size sin usar
: _nVertices { nVertices }
{
	GLHE_(glGenBuffers(1, &_VBO_ID[count]));
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID[count]));
	GLHE_(glBufferData(GL_ARRAY_BUFFER, _nVertices, data, GL_STATIC_DRAW));
	++count;
}
void vbo_t::set(const void* data, const uint32_t nVertices) 
{
	_nVertices = nVertices;
	GLHE_(glGenBuffers(1, &_VBO_ID[count]));
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID[count]));
	GLHE_(glBufferData(GL_ARRAY_BUFFER, _nVertices, data, GL_STATIC_DRAW));
	

	std::cout << "VBO " << count << " setted" << std::endl;

	++count;
}

vbo_t::~vbo_t() 
{
	for (int i = 0; i < count; ++i)
		glDeleteBuffers(1, &_VBO_ID[i]);
}



void vbo_t::bind() const
{
	for (int i = 0; i < count; i++)		
		glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID[i]);
}

void vbo_t::unbind() const
{
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

} // namespace TFM_ECS