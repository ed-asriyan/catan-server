#include "game.hpp"

Game::Game()
{
	not_using_colors_ = { ORANGE, BLUE, WHITE, RED };
	board.deployment();
}

Game::Game(int gameID)
{
	gameID_ = gameID;
	board.deployment();
}

Game::~Game()
{

}

int Game::getID()
{
	return gameID_;
}

void Game::showTypes()
{
	for (int i = -2; i < FIELD_SIZE; ++i) {
		for (int j = -2; j < FIELD_SIZE; ++j) {
			if (i == -2 && j == -2) {
				cout << "  ";
			} else if (i == -2 && j > -1) {
				if (j > 9)
					cout << j;
				else 
					cout << '0' << j;
			} else if (i == -1) {
				cout << "----";
			} else if (j == -2) {
				if (i > 9)
					cout << i;
				else
					cout << '0' << i;
			} else if (j == -1) {
				cout << "| ";
			} else {
				switch (board.getCellType({i, j})) {
					case BLANK_CELL:
						cout << "X ";
						break;
					case GEXAGON:
						cout << "G ";
						break;
					case INTERSECTION:
						cout << "O ";
						break;
					case EDGE:
						cout << "= ";
						break;
				}
			}
			cout << "| ";
		}
		cout << endl;
	}
}

int Game::playersAmount()
{
	return playersAmount_;
}

void Game::addPlayer(const Color col)
{
	if (col != NO_COLOR)
	{
		auto col_it = find(not_using_colors_.begin(), not_using_colors_.end(), col);
		if (col_it < not_using_colors_.end())
		{
			Player new_player(col);
			players_.push_back(new_player);
			not_using_colors_.erase(col_it);
		}
	}
	else
	{
		if (not_using_colors_.size() > 0)
		{
			Player new_player(not_using_colors_[0]);
			players_.push_back(new_player);
			not_using_colors_.erase(not_using_colors_.begin());
		}
	}
}
