#pragma once
#include <memory>

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

	
	// Unique Pointer - Scope for control lifetime and other things
	template<typename T>
	using Unique = std::unique_ptr<T>;


	// Shared pointer - sistema de conteo de referencia -
	template<typename T>	
	using RefCount = std::shared_ptr<T>;

	
}

