// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Engine.h"
#include <vld.h>

int main()
{
	auto game = svp::Engine();
	game.Run();
}

