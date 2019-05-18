#pragma once
#include "Singleton.h"

namespace svp
{
	class Logger final : public Singleton<Logger>
	{
	public:
		enum LogType
		{
			Error,
			Warning,
			Debug
		};

		Logger() = default;

		void Log(LogType type, const std::string& message);
	};
}