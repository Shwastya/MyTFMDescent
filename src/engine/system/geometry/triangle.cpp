#include "engine/system/geometry/triangle.hpp"
#include <vcruntime_string.h>


namespace MHelmet
{
	Triangle::Triangle()
	{
		m_Vertices = 3;
		m_Elements = 3;

		float triangle[27] =
		{
			// positions		  // UVS
			-0.5f, -0.5f, 0.0f,	  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,   1.0f, 1.0f,	0.0f, 0.0f, 1.0f
		};

		memcpy(m_Triangle, triangle, sizeof(triangle));

		for (size_t i = 0; i < 3; ++i) m_Indices[i] = i;

	}

	float* Triangle::GetModel() { return m_Triangle; }

	uint32_t* Triangle::Indices() { return m_Indices; }

	size_t Triangle::Size() const
	{
		return sizeof(m_Triangle);
	}

	uint32_t Triangle::Count() const
	{
		return sizeof(m_Indices) / sizeof(uint32_t);
	}
}

