#pragma once
#include <vector>
#include <cstdint>
#include "engine/system/handleGLerrors.hpp"


namespace TFM_ECS {

struct vbe_t // vertex buffer element
{
								// count, type    , normalize   
	// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0)
	uint32_t type;
	uint32_t count;	
	unsigned char normalized;
	std::string name = "noname";
	
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

	vbl_t(const vbl_t&) = default;
	vbl_t& operator=(const vbl_t&) = default;

	vbl_t(vbl_t&&) noexcept = default;
	vbl_t& operator=(vbl_t&&) noexcept = default;

	
	template<typename T>		
	void push(const uint32_t count, const std::string name = "empty")
	{
		
		static_assert(count == -1, "Implemented for overload push function");
	}

	const std::vector<vbe_t> getElements() const { return _elements; }
	uint32_t getStride() const { return _stride; } 
};


template<>
inline void vbl_t::push<float>(const uint32_t count, const std::string name)
{
	std::cout << "type:   GL_FLOAT" << count << std::endl;
	_elements.push_back({GL_FLOAT, count, GL_FALSE, name});
	_stride += count * vbe_t::getSizeOfType(GL_FLOAT);
}

template<>
inline void vbl_t::push<uint32_t>(const uint32_t count, const std::string name)
{
								// count, type    , normalize   
// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0)
	std::cout << "type:   GL_UNSIGNED_INT" << count << std::endl;
	_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE, name});
	_stride += count * vbe_t::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void vbl_t::push<unsigned char>(const uint32_t count, const std::string name)
{
	std::cout << "type:   GL_UNSIGNED_BYTE" << count << std::endl;
	_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE, name});
	_stride += count * vbe_t::getSizeOfType(GL_UNSIGNED_BYTE);
}
}
