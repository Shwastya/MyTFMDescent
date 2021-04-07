#include "engine/object/ebo.hpp"
#include "engine/system/handleGLerrors.hpp"


namespace TFM_ECS {


ebo_t::ebo_t(const uint32_t* data, const uint32_t nElements) // size sin usar
: _nElements  {  nElements  }
{	
	GLHE_(glGenBuffers(1, &_EBO_ID));
	GLHE_(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO_ID));
   GLHE_(glBufferData(GL_ELEMENT_ARRAY_BUFFER, _nElements, data, GL_STATIC_DRAW));
}

ebo_t::~ebo_t() 
{
	GLHE_(glDeleteBuffers(1, &_EBO_ID));
}

void ebo_t::bind() const
{
	GLHE_(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO_ID));
}

void ebo_t::unbind() const
{
	GLHE_(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace TFM_ECS