#pragma once
#include <vector>
#include "engine/system/handleGLerrors.hpp"


namespace TFM_ECS {

struct vbe_t // vertex buffer element
{
								// count, type    , normalize   
	// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0)
	u_int32_t type;
	u_int32_t count;	
	u_char    normalized;

	static unsigned int getSizeOfType(uint32_t type)
	{
		switch (type)
		{
			case GL_FLOAT: 		  return 4; break;
			case GL_UNSIGNED_INT:  return 4; break;
			case GL_UNSIGNED_BYTE: return 1; break;		
		}
		ASSERT(false);
		return 0;
	}	
};

class vbl_t
{

	private:
	std::vector<vbe_t> _elements; // layout vertex buffer elements
	uint32_t _stride;


public:

	vbl_t() :_stride{0} {}

	
	template<typename T>		
	void push(uint32_t count)
	{
		std::cout << "template count: " << count << std::endl;
		static_assert(false, "this function has to be implemented for desired type");
	}

	const std::vector<vbe_t> getElements() const { return _elements; }
	uint32_t getStride() const { return _stride; } 
};


template<>
inline void vbl_t::push<float>(uint32_t count)
{
	std::cout << "type:   GL_FLOAT" << count << std::endl;
	_elements.push_back({GL_FLOAT, count, GL_FALSE});
	_stride += count * vbe_t::getSizeOfType(GL_FLOAT);
}

template<>
inline void vbl_t::push<uint32_t>(uint32_t count)
{
								// count, type    , normalize   
// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0)
	std::cout << "type:   GL_UNSIGNED_INT" << count << std::endl;
	_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	_stride += count * vbe_t::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void vbl_t::push<u_char>(uint32_t count)
{
	std::cout << "type:   GL_UNSIGNED_BYTE" << count << std::endl;
	_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	_stride += count * vbe_t::getSizeOfType(GL_UNSIGNED_BYTE);
}
}
