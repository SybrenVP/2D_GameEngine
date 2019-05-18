// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#pragma comment(lib,"xinput.lib")

#include <iostream>
#include <vld.h>
#include "SDL.h"
#include "Engine.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[])
{
#pragma warning( pop )
	svp::Engine engine{};
	engine.Run();
	return 0;
}
