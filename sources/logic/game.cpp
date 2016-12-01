#include "game.hpp"

Game::Game()
{
	not_using_colors_ = { ORANGE, BLUE, WHITE, RED };
	board.deployment();
	srand(time(0));
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

void Game::show()
{
	board.show();

	cout << endl << endl;

	for (auto p : players_)
	{
		switch (p.first)
		{
			case 0:
				cout << "NO_COLOR" << endl;
				break;
			case 1:
				cout << "ORANGE" << endl;
				break;
			case 2:
				cout << "BLUE" << endl;
				break;
			case 3:
				cout << "WHITE" << endl;
				break;
			case 4:
				cout << "RED" << endl;
				break;
		}
		p.second.show();
		cout << endl;
	}
}

int Game::playersAmount()
{
	return playersAmount_;
}

void Game::addPlayer(Color col)
{
	if (col != NO_COLOR)
	{
		auto col_it = find(not_using_colors_.begin(), not_using_colors_.end(), col);
		if (col_it < not_using_colors_.end())
		{
			++playersAmount_;
			Player new_player;
			// players_.push_back(new_player);
			players_[col] = new_player;
			not_using_colors_.erase(col_it);
			board.playerInitDeployment(col);
		}
	}
	else
	{
		if (not_using_colors_.size() > 0)
		{
			++playersAmount_;
			col = not_using_colors_[0];
			Player new_player;
			// players_.push_back(new_player);
			players_[col] = new_player;
			board.playerInitDeployment(col);
			not_using_colors_.erase(not_using_colors_.begin());
		}
	}

}

int Game::throwDice()
{
	// srand(time(0));

	// 1 to 6
	int dice1 = rand() % 6 + 1;
	int dice2 = rand() % 6 + 1;

	// 2 to 12
	return dice1 + dice2;
}

void Game::nextStep()
{
	int dice = throwDice();

	if (dice != 7)
	{
		vector<Coordinates> gexes = board.getGexesByNumber(dice);
		for (auto gex : gexes)
		{
			Resource resource = board.getGexResource(gex);
			vector<Coordinates> intersections = board.getIntersectionsByGex(gex);
			for (auto isect : intersections)
			{
				auto cell = dynamic_cast<Intersection*>(board[isect]);
				if (cell->building.type != NO_BUILDING)
				{
					Color color = cell->building.color;
					int amount = 0;
					if (cell->building.type == SETTLEMENT)
					{
						amount = 1;
					}
					else if (cell->building.type == CITY)
					{
						amount = 2;
					}

					players_[color].addResource(resource, amount);
				}
			}
		}
	}

	cout << endl << dice << endl;
}

// void Game::build(BuildingType type, Color color, Coordinates coord)
// {
// 	if (board[coord]->building.type != NO_BUILDING || color == NO_COLOR)
// 	{
// 		return;
// 	}


// }

bool Game::buyBuilding(Color color, BuildingType type)
{
	for (auto cost : costs_[type])
	{
		if (!players_[color].haveResourse(cost.first, cost.second))
		{
			return false;
		}
	}

	for (auto cost : costs_[type])
	{
		players_[color].takeResource(cost.first, cost.second);
	}

	return true;
}

// void Game::buildRoad(Color color, Coordinates coord)
// {
// 	if (board.canBuildRoad(color, coord))
// 	{
// 		if (buyBuilding(color, ROAD))
// 		{
// 			board[coord]->building.type = ROAD;
// 			board[coord]->building.color = color;
// 		}
// 	}
// }

// void Game::buildSettlement(Color color, Coordinates coord)
// {
// 	if (board.canBuildSettlement(color, coord))
// 	{
// 		if (buyBuilding(color, SETTLEMENT))
// 		{
// 			board[coord]->building.type = SETTLEMENT;
// 			board[coord]->building.color = color;
// 		}
// 	}
// }

// void Game::buildCity(Color color, Coordinates coord)
// {
// 	if (board.canBuildCity(color, coord))
// 	{
// 		if (buyBuilding(color, CITY))
// 		{
// 			board[coord]->building.type = CITY;
// 			board[coord]->building.color = color;
// 		}
// 	}
// }

void Game::build(BuildingType type, Color color, Coordinates coord)
{
	if (board.canBuild(type, color, coord))
	{
		if (buyBuilding(color, type))
		{
			board[coord]->building.type = type;
			board[coord]->building.color = color;
		}
	}
}
