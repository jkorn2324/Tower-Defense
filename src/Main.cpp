#include <iostream>
#include "Game.h"

int main(int argsCount, char** args)
{
	TowerDefense::Game game;
	if (game.InitializeGame())
	{
		game.RunGame();
	}
	game.ShutdownGame();
	return 0;
}