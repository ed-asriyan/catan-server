#include "game.hpp"

Game::Game()
{
	initialization();
}

Game::Game(int gameID)
{
	gameID_ = gameID;
	initialization();
}

Game::~Game()
{
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			delete playingFied_[i][j];
		}
	}
}

void Game::initialization()
{
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			playingFied_[i][j] = NULL;
		}
	}

	int x_coord = 0;
	int y_coord = 0;
	for (unsigned int i = 0; i < gexagonCoordinates_.size(); ++i) {
		x_coord = gexagonCoordinates_[i].x;
		y_coord = gexagonCoordinates_[i].y;

		playingFied_[x_coord][y_coord] = new Gexagon;

		playingFied_[x_coord + 2][y_coord] = new Intersection;
		playingFied_[x_coord - 2][y_coord] = new Intersection;
		playingFied_[x_coord][y_coord + 2] = new Intersection;
		playingFied_[x_coord][y_coord - 2] = new Intersection;
		playingFied_[x_coord + 2][y_coord - 2] = new Intersection;
		playingFied_[x_coord - 2][y_coord + 2] = new Intersection;

		playingFied_[x_coord - 1][y_coord - 1] = new Edge;
		playingFied_[x_coord + 1][y_coord + 1] = new Edge;
		playingFied_[x_coord + 1][y_coord - 2] = new Edge;
		playingFied_[x_coord + 2][y_coord - 1] = new Edge;
		playingFied_[x_coord - 1][y_coord + 2] = new Edge;
		playingFied_[x_coord - 2][y_coord + 1] = new Edge;
	}

	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			if (!playingFied_[i][j]) {
				playingFied_[i][j] = new BlankCell;
			}			
		}
	}
}

void Game::deployment()
{
	map<Resource, vector<int>> resourcesPlacement = {
		{NOTHING, {18}},
		{WOOD, {3, 7, 11, 12}},
		{BRICKS, {1, 13, 15}}, 
		{FLEECE, {2, 8, 9, 17}}, 
		{CORN, {0, 4, 5, 10}}, 
		{ORE, {6, 14, 16}}
	};

	for (auto it_map = resourcesPlacement.begin(); it_map != resourcesPlacement.end(); ++it_map) {
		for (auto it_vect = it_map->second.begin(); it_vect != it_map->second.end(); ++it_vect) {
			Coordinates coord = gexagonCoordinates_[*it_vect];

			// Кинуть exception, если тип ячейки не тот
			
			Gexagon* gex = dynamic_cast<Gexagon*>(playingFied_[coord.x][coord.y]);
			gex->resource = it_map->first;
		}
	}

	for (int i = 0; i < GEX_AMOUNT; ++i) {
		Coordinates coord = gexagonCoordinates_[i];
		Gexagon* gex = dynamic_cast<Gexagon*>(playingFied_[coord.x][coord.y]);
		cout << i << ' ' << gex->resource << endl;
	}

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
				cout << "\\\\";
			} else if (i == -2 && j > -1) {
				if (j > 9)
					cout << j;
				else 
					cout << '0' << j;
			} else if (i == -1) {
				cout << "--";
			} else if (j == -2) {
				if (i > 9)
					cout << i;
				else
					cout << '0' << i;
			} else if (j == -1) {
				cout << '|';
			} else {
				switch (getCellType({i, j})) {
					case BLANK_CELL:
						cout << 'X';
						break;
					case GEXAGON:
						cout << 'G';
						break;
					case INTERSECTION:
						cout << 'O';
						break;
					case EDGE:
						cout << '=';
						break;
				}
				cout << '|';
			}
		}
		cout << endl;
		
	}
}

CellType Game::getCellType(Coordinates coord)
{
	return playingFied_[coord.x][coord.y]->type();
}

int Game::playersAmount()
{
	return playersAmount_;
}
