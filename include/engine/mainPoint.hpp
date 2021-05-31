#pragma once
#include <MHelmet.h>

#include <iostream>
#include "windows.h"      // is a Windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API, all the common macros used by Windows programmers, and all the data types used by the various functions and subsystems.
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>       // including dynamic memory management, random number generation, communication with the environment, integer arithmetics, searching, sorting and converting.
#include <crtdbg.h>       //for malloc and free

static void CheckLeaks(int snapshot)
{
	static _CrtMemState sOld;
	static _CrtMemState sNew;
	static _CrtMemState sDiff;
	if (snapshot == 1)
	{
		_CrtMemCheckpoint(&sOld); //take a snapshot
	}
	else
	{
		_CrtMemCheckpoint(&sNew); //take a snapchot 
		if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
		{
			OutputDebugString(L"--------_CrtMemDumpStatistics ------> ");
			_CrtMemDumpStatistics(&sDiff);
			OutputDebugString(L"--------_CrtMemDumpAllObjectsSince -> ");
			_CrtMemDumpAllObjectsSince(&sOld);
			OutputDebugString(L"--------_CrtDumpMemoryLeaks --------> ");
			_CrtDumpMemoryLeaks();
		}
	}
}
/**************************************
*  main() punto de entrada proyectos  *
* *************************************/

extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp();

int main(int argc, char** argv )
{	
	//MHelmet::Log::Init();
	//MHelmet::Log::GetCoreLogger()->warn("Initialized Log System!");
	//MHelmet::Log::GetClientLogger()->info("[EntryPoint]-> calls create application");
	CheckLeaks(1);
	{
		MHelmet::LogManager::p().log().GetClientLogger()->warn("Initialized Log System!");

		MHelmet::LogManager::p().switchLog(MHelmet::LogType::STRATEGY2);

		MHelmet::LogManager::p().log().GetClientLogger()->warn("Cambio de sistema de Log!");

		//MHelmet::LogManager::p().switchLog(MHelmet::LogType::STRATEGY1);

		MHelmet::LogManager::p().log().GetClientLogger()->warn("Vuelvo a cambiar en tiempo de ejecucion!");

		auto project = MHelmet::createApp();
		project->run();
	}
	CheckLeaks(2);

	
	return 0;
}