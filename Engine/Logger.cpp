#include "pch.h"
#include "Logger.h"

void svp::Logger::Log(LogType type, const std::string & message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (type)
	{
	case LogType::Error:
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "!! > ERROR: " << message << '\n';
		break;
	case LogType::Warning:
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << "> WARNING: " << message << '\n';
		break;
	case LogType::Debug:
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "Debug info: " << message << '\n';
		break;
	default:
		Log(LogType::Error, "No acceptable logtype used in the logger.");
	}
	
	SetConsoleTextAttribute(hConsole, 15); //Setting back to default
}
