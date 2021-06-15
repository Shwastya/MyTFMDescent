#pragma once

namespace MHelmet
{
	struct DeltaTime
	{
		DeltaTime(float time = 0) :m_Time(time)
		{}

		float Seconds() const { return m_Time;  }
		float MilliSeconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};


	
}

/* MUUUUUUY TEMPORAL */
#include <glm/glm.hpp>
struct ModelTransform
{
	glm::vec3 Translate = glm::vec3(1.0f);
	glm::vec3 Rotate    = glm::vec3(1.0f);
	float Degrees		= 0.0f;	
	glm::vec3 Scale     = glm::vec3(1.0f);
		
};