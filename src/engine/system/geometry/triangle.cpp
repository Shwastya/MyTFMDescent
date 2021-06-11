#include "engine/system/geometry/triangle.hpp"
#include <vcruntime_string.h>


namespace MHelmet
{
	Triangle::Triangle()
	{
		m_Vertices = 3;
		m_Elements = 3;

		float positions[9] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		memcpy(m_Positions, positions, sizeof(positions));

		for (size_t i = 0; i < 3; ++i) m_Indices[i] = i;

	}

	float* Triangle::Positions() { return m_Positions; }

	uint32_t* Triangle::Indices() { return m_Indices; }

	size_t Triangle::Size() const
	{
		return sizeof(m_Positions);
	}

	uint32_t Triangle::Count() const
	{
		return m_Elements;
	}
}

