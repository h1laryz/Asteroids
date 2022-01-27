#include <iostream>
#include "Game.h"

// { "game.exe", "-window", "800x600", "-map", "1000x1000", "-num_asteroids", "10", "-num_ammo", "3", "-ability_probability 0.3" };

int main(int argc, char *argv[])
{
	srand(time(0));
	Game game(argc, argv);
	return run(&game);
}
