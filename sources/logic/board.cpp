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
		// cout << i << ' ' << gex->resource << endl;
	}
}

CellType Board::getCellType(Coordinates coord)
{
	return playingFied_[coord.x][coord.y]->type();
}

void Board::playerInitDeployment(const Color col)
{
	auto vect = init_pos[col];
	for (auto it_vect : vect)
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

Resource Board::getGexResource(Coordinates coord)
{
	Cell* cell = playingFied_[coord.x][coord.y];

	if (cell->type() != GEXAGON)
	{
		return NOTHING;
	}
	else
	{
		auto gex = dynamic_cast<Gexagon*>(cell);
		return gex->resource;
	}
}

vector<Coordinates> Board::getGexesByNumber(int num)
{
	return gex_numbers_[num];
}

// vector<Coordinates> Board::getIntersectionsByNumber(int num)
// {
// 	vector<Coordinates> gexes = gex_numbers_[num];

// }

vector<Coordinates> Board::getEdgesByEdge(Coordinates coord)
{
	vector<Coordinates> answer;

	for (int i = -2; i < 3; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			int x = coord.x + i;
			int y = coord.y + j;
			Cell* cell = playingFied_[x][y];
			if (cell->type() == EDGE)
			{
				answer.push_back({x, y});
			}
		}
	}

	return answer;
}

vector<Coordinates> Board::getIntersectionsByIntersection(Coordinates coord)
{
	vector<Coordinates> answer;

	for (int i = -2; i < 3; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			int x = coord.x + i;
			int y = coord.y + j;
			Cell* cell = playingFied_[x][y];
			Cell* cell_between = playingFied_[(x + coord.x) / 2][(y + coord.y) / 2];
			if (cell->type() == INTERSECTION && cell_between->type() == EDGE)
			{
				answer.push_back({x, y});
			}
		}
	}

	return answer;
}	

vector<Coordinates> Board::getIntersectionsByGex(Coordinates coord)
{
	vector<Coordinates> answer;

	for (int i = -2; i < 3; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			int x = coord.x + i;
			int y = coord.y + j;
			Cell* cell = playingFied_[x][y];
			if (cell->type() == INTERSECTION)
			{
				answer.push_back({x, y});
			}
		}
	}

	return answer;
}

vector<Coordinates> Board::getEdgesByGex(Coordinates)
{

}

vector<Coordinates> Board::getGexesByIntersection(Coordinates)
{

}

vector<Coordinates> Board::getEdgesByIntersection(Coordinates coord)
{
	vector<Coordinates> answer;

	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			int x = coord.x + i;
			int y = coord.y + j;
			Cell* cell = playingFied_[x][y];
			if (cell->type() == EDGE)
			{
				answer.push_back({x, y});
			}
		}
	}

	return answer;
}

vector<Coordinates> Board::getIntersectionsByEdge(Coordinates coord)
{
	vector<Coordinates> answer;

	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			int x = coord.x + i;
			int y = coord.y + j;
			Cell* cell = playingFied_[x][y];
			if (cell->type() == INTERSECTION)
			{
				answer.push_back({x, y});
			}
		}
	}

	return answer;
}

vector<Coordinates> Board::getGexesByEdge(Coordinates)
{

}

bool Board::canBuildRoad(Color color, Coordinates coord)
{
	if (playingFied_[coord.x][coord.y]->building.type != NO_BUILDING)
	{
		cout << "Can not build road in " << coord << endl;
		cout << playingFied_[coord.x][coord.y]->building.type << " is here" << endl;
		return false;
	}

	vector<Coordinates> nearby_edges = getEdgesByEdge(coord);

	for (auto edge : nearby_edges)
	{
		if (playingFied_[edge.x][edge.y]->building.color == color)
		{
			cout << "Can build road in " << coord << endl;
			return true;
		}
	}

	cout << "Can not build road in " << coord << endl;
	cout << "End of func" << endl;
	return false;
}

bool Board::canBuildSettlement(Color color, Coordinates coord)
{
	if (playingFied_[coord.x][coord.y]->building.type != NO_BUILDING)
	{
		cout << "Can not build settlement in " << coord << endl;
		cout << playingFied_[coord.x][coord.y]->building.type << " is here" << endl;
		return false;
	}

	vector<Coordinates> nearby_intersections = getIntersectionsByIntersection(coord);

	for (auto isect : nearby_intersections)
	{
		if (playingFied_[isect.x][isect.y]->building.type != NO_BUILDING)
		{
			cout << "Can not build settlement in " << coord << endl;
			cout << playingFied_[isect.x][isect.y]->building.type << " in " << isect << endl;
			return false;
		}
	}

	vector<Coordinates> nearby_edges = getEdgesByIntersection(coord);

	for (auto edge : nearby_edges)
	{
		if (playingFied_[edge.x][edge.y]->building.color == color)
		{
			cout << "Can build settlement in " << coord << endl;
			return true;
		}
	}

	cout << "Can not build settlement in " << coord << endl;
	cout << "End of func" << endl;
	return false;
}

bool Board::canBuildCity(Color color, Coordinates coord)
{
	if (playingFied_[coord.x][coord.y]->building.type != SETTLEMENT)
	{
		cout << "Can not build city in {" << coord.x << ", " << coord.y << "}" << endl;
		cout << playingFied_[coord.x][coord.y]->building.type << " is here" << endl;
		return false;
	}

	cout << "Can build city in {" << coord.x << ", " << coord.y << "}" << endl;
	return true;
}

bool Board::canBuild(BuildingType type, Color color, Coordinates coord)
{
	if (color == NO_COLOR)
	{
		cout << "Can not build in {" << coord.x << ", " << coord.y << "}" << endl;
		cout << "No color" << endl;
		return false;
	}

	if (playingFied_[coord.x][coord.y]->type() != BuildToCellType(type))
	{
		cout << "Can not build in {" << coord.x << ", " << coord.y << "}" << endl;
		cout << "Wrong cell type" << endl;
		return false;
	}

	switch (type)
	{
		case ROAD:
			return canBuildRoad(color, coord);
		case SETTLEMENT:
			return canBuildSettlement(color, coord);
		case CITY:
			return canBuildCity(color, coord);
		default:
			cout << "Can not build in {" << coord.x << ", " << coord.y << "}" << endl;
			cout << "Default case" << endl;
			return false;
	}

	cout << "Can not build in {" << coord.x << ", " << coord.y << "}" << endl;
	cout << "End of function" << endl;
	return false;
}


Cell* Board::operator[](Coordinates crd)
{
	return playingFied_[crd.x][crd.y];
}

void Board::show()
{
	for (int i = -1; i < FIELD_SIZE; ++i) {
		for (int j = -1; j < FIELD_SIZE; ++j) {
			if (i == -1 && j == -1) {
				cout << "  ";
			} else if (i == -1 && j > -1) {
				cout << " " << j;
				if (j < 10)
					cout << " ";
				// if (j > 9)
				// 	cout << " " << j;
				// else 
				// 	cout << " " << j << " ";
			} else if (j == -1) {
				if (i > 9)
					cout << i;
				else
					cout << " " << i;
			} else {
				int text_color = C_Reset;
				int city = 0;
				BuildingType type = playingFied_[i][j]->building.type;
				if (type != NO_BUILDING)
				{
					if (type == CITY)
					{
						city = 1;
					}
					Color color = playingFied_[i][j]->building.color;
					switch (color)
					{
						case ORANGE:
							text_color = C_Brown;
							break;
						case BLUE:
							text_color = C_Blue;
							break;
						case WHITE:
							text_color = C_Invers;
							break;
						case RED:
							text_color = C_Red;
							break;
					}
				}

				char gex = 'G';

				if (getCellType({i, j}) == GEXAGON)
				{
					Gexagon* gexagon = dynamic_cast<Gexagon*>(playingFied_[i][j]);
					Resource res = gexagon->resource;
					switch (res)
					{
						case WOOD:
							gex = 'W';
							break;
						case BRICKS:
							gex = 'B';
							break;
						case FLEECE:
							gex = 'F';
							break;
						case CORN:
							gex = 'C';
							break;
						case ORE:
							gex = 'O';
							break;
					}
				}

				switch (getCellType({i, j})) {
					case BLANK_CELL:
						cout << " . ";
						break;
					case GEXAGON:
						cout << "{" << gex << "}";
						break;
					case INTERSECTION:
						// cout << "O ";
						printf(" \033[%dm\033[%dm\033[%dmO\033[0m ", tcolor[city], tcolor[C_Invers], tcolor[text_color]);
						break;
					case EDGE:
						// cout << "= ";
						printf(" \033[%dm\033[%dm=\033[0m ", tcolor[C_Invers], tcolor[text_color]);
						break;
				}
			}
			cout << "|";
		}
		cout << endl;
	}
}