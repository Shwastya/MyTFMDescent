#include "engine/object/vbo.hpp"
#include "engine/system/handleGLerrors.hpp"


namespace TFM_ECS {


vbo_t::vbo_t(const void* data, const uint32_t nVertices) // size sin usar
: _nVertices { nVertices }
{
	GLHE_(glGenBuffers(1, &_VBO_ID));
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID));
	GLHE_(glBufferData(GL_ARRAY_BUFFER, _nVertices, data, GL_STATIC_DRAW));
}
void vbo_t::setBufferObject(const void* data, const uint32_t nVertices) 
{
	_nVertices = nVertices;
	GLHE_(glGenBuffers(1, &_VBO_ID));
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID));
	GLHE_(glBufferData(GL_ARRAY_BUFFER, _nVertices, data, GL_STATIC_DRAW));
}

vbo_t::~vbo_t() 
{
	GLHE_(glDeleteBuffers(1, &_VBO_ID));
}



void vbo_t::bind() const
{
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID));
}

void vbo_t::unbind() const
{
	GLHE_(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

} // namespace TFM_ECS