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

