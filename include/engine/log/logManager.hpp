#pragma once
#include "engine/log/log.hpp"
;

namespace MHelmet {

	enum class LogType 
	{
		STRATEGY1, STRATEGY2
	};

	class LogManager
	{
	public:
		~LogManager();

		static LogManager& p();

		Log& log();

		void switchLog(const LogType type);

	private:
		LogManager();

		/*LogManager(const LogManager& other) = delete;

		LogManager(LogManager&& other)  noexcept
			: m_selected(other.m_selected)
		{
			m_Log = other.m_Log;
			printf("Move\n");
		}

		LogManager& operator = (const LogManager& other) = delete;


		LogManager& operator = (LogManager&& other) noexcept
		{
			
			return *this;
		}*/

		/// Atributes
		Log* m_Log = nullptr;
		LogType m_selected = LogType::STRATEGY1;
		
	};


}