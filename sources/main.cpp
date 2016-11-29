#include <iostream>

#include "logic/game.hpp"
#include "translate/translate.hpp"

int main(int argc, char const *argv[])
{
	Game game;
	game.showTypes();

	// cout << game.getCellType({10, 10}) << endl;
	// game.deployment();

	return 0;
}