#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include "cell.hpp"
#include "board.hpp"
#include "player.hpp"

class Game
{
public:
	Game();
	Game(int gameID);
	~Game();

	int getID();
	void showTypes();
	int playersAmount();
	void addPlayer(Color col = NO_COLOR);

	void throwDice();

private:
	Board board;
	int gameID_;
	int playersAmount_;
	vector<Player> players_;
	vector<Color> not_using_colors_;
	
};

#endif