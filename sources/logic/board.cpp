#include "board.hpp"

Board::Board()
{
	initialization();
}

Board::~Board()
{
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			delete playingFied_[i][j];
		}
	}
}

void Board::initialization()
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

void Board::deployment(DeploymentType type)
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

CellType Board::getCellType(Coordinates coord)
{
	return playingFied_[coord.x][coord.y]->type();
}

void Board::playerInitDeployment(Color col)
{
	map<Color, vector<Coordinates>> init_pos = {
		{ ORANGE, {
			{ 8,  4}, { 9,  3}, {16,  8}, {15,  9}
		} }, 
		{ BLUE, {
			{ 6,  8}, { 7,  7}, { 8, 16}, { 9, 15}
		} },
		{ WHITE, {
			{ 6, 14}, { 5, 14}, {14, 12}, {13, 13}
		} },
		{ RED, {
			{ 4, 12}, { 5, 11}, {14,  6}, {14,  5}
		} }	
	};

	for (auto it_vect : init_pos[col])
	{
		Coordinates crd = it_vect;
		CellType type = getCellType(crd);
		if (type == INTERSECTION)
		{
			playingFied_[crd.x][crd.y]->building = { SETTLEMENT, col };
		}
		else if (type == EDGE)
		{
			playingFied_[crd.x][crd.y]->building = { ROAD, col };
		}
	}
}