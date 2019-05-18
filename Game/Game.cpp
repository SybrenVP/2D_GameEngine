// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Engine.h"

int main()
{
	auto game = new svp::Engine();
	game->Run();
}

