#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "cell.hpp"
#include "board.hpp"
#include "player.hpp"

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

private:
	int throwDice();
	bool buyBuilding(Color, BuildingType);

	Board board;
	vector<Color> not_using_colors_;

	map<Color, Player> players_;

	map<BuildingType, map<Resource, int>> costs_ = {
		{ NO_BUILDING, {} }, 
		{ SETTLEMENT, {
			{ WOOD, 1 }, { BRICKS, 1 }, { FLEECE, 1 }, { CORN, 1 }
		} },
		{ CITY , {
			{ CORN, 2 }, { ORE, 3 }
		} },
		{ ROAD, {
			{ WOOD, 1 }, { BRICKS, 1 }
		} }
	};
};

#endif