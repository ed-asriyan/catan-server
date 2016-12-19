#include "game.hpp"

Game::Game()
{
	not_using_colors_ = { ORANGE, BLUE, WHITE, RED };
	board.deployment();
	srand(time(0));
}

Game::~Game()
{

}

void Game::show()
{
	board.show();

	cout << endl << endl;

	for (auto p : players_)
	{
		cout << p.first << endl;
		p.second.show();
		cout << endl;
	}
}

void Game::addPlayer(Color col)
{
	auto col_it = not_using_colors_.begin();

	if (col != NO_COLOR)
	{
		col_it = find(not_using_colors_.begin(), not_using_colors_.end(), col);
	}

	if (col_it < not_using_colors_.end())
	{
		col = *col_it;
		Player new_player;
		players_[col] = new_player;
		board.playerInitDeployment(col);
		not_using_colors_.erase(col_it);
	}
}

int Game::throwDice()
{
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
		// vector<Coordinates> gexes = board.getGexesByNumber(dice);
		auto gex = GexesByNumberIterator(board, dice);
		for ( ; gex(); ++gex)
		{
			Resource resource = board.getGexResource(*gex);
			// vector<Coordinates> intersections = board.getIntersectionsByGex(*gex);
			auto isect = IntersectionsByGexIterator(board, *gex);
			for ( ; isect(); ++isect)
			{
				Cell cell = board[*isect];
				if (cell.building.type != NO_BUILDING)
				{
					Color color = cell.building.color;
					int amount = 0;
					if (cell.building.type == SETTLEMENT)
					{
						amount = 1;
					}
					else if (cell.building.type == CITY)
					{
						amount = 2;
					}

					players_[color].addResource(resource, amount);
				}
			}
		}
	}

	cout << "dice: " << dice << endl;
}

bool Game::buyBuilding(Color color, BuildingType type)
{
	for (auto cost : Settings::costs[type])
	{
		if (!players_[color].haveResourse(cost.first, cost.second))
		{
			return false;
		}
	}

	for (auto cost : Settings::costs[type])
	{
		players_[color].takeResource(cost.first, cost.second);
	}

	return true;
}

void Game::build(BuildingType type, Color color, Coordinates coord)
{
	if (board.canBuild(type, color, coord))
	{
		if (buyBuilding(color, type))
		{
			board[coord].building.type = type;
			board[coord].building.color = color;
			cout << color << " " << type << " is build in " << coord << endl;
		}
		else
		{
			cout << "No resources for build " << color << " " << type << " in " << coord << endl;
		}
	}
}
