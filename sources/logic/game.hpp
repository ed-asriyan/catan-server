#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "board.hpp"
#include "player.hpp"
#include "settings.hpp"

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void show();
	void addPlayer(Color col = NO_COLOR);
	void nextStep();
	void build(BuildingType, Color, Coordinates);
	vector<Color> checkWinners();

private:
	int throwDice();
	bool buyBuilding(Color, BuildingType);

	Board board;
	vector<Color> not_using_colors_;
	map<Color, Player> players_;
};

#endif