#include "board.hpp"

Board::Board()
{
	initialization();
}

Board::~Board()
{
	// for (int i = 0; i < FIELD_SIZE; ++i) {
	// 	for (int j = 0; j < FIELD_SIZE; ++j) {
	// 		delete playingFied_[i][j];
	// 	}
	// }
}

void Board::initialization()
{
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			playingFied_[i][j] = {
				BLANK_CELL,
				{ NO_BUILDING, NO_COLOR },
				NOTHING,
				{ NO_HARBOR, NOTHING }
			};
		}
	}

	Coordinates coord = {0, 0};
	
	// for (unsigned int i = 0; i < gexagonCoordinates_.size(); ++i) {
	// 	coord = gexagonCoordinates_[i];

	// 	playingFied_[coord.x][coord.y].type = GEXAGON;

	// 	playingFied_[coord.x + 2][coord.y].type = INTERSECTION;
	// 	playingFied_[coord.x - 2][coord.y].type = INTERSECTION;
	// 	playingFied_[coord.x][coord.y + 2].type = INTERSECTION;
	// 	playingFied_[coord.x][coord.y - 2].type = INTERSECTION;
	// 	playingFied_[coord.x + 2][coord.y - 2].type = INTERSECTION;
	// 	playingFied_[coord.x - 2][coord.y + 2].type = INTERSECTION;

	// 	playingFied_[coord.x - 1][coord.y - 1].type = EDGE;
	// 	playingFied_[coord.x + 1][coord.y + 1].type = EDGE;
	// 	playingFied_[coord.x + 1][coord.y - 2].type = EDGE;
	// 	playingFied_[coord.x + 2][coord.y - 1].type = EDGE;
	// 	playingFied_[coord.x - 1][coord.y + 2].type = EDGE;
	// 	playingFied_[coord.x - 2][coord.y + 1].type = EDGE;
	// }	

	for (auto it = BoardGexIterator(*this); it(); ++it)
	{
		coord = *it;

		playingFied_[coord.x][coord.y].type = GEXAGON;

		playingFied_[coord.x + 2][coord.y].type = INTERSECTION;
		playingFied_[coord.x - 2][coord.y].type = INTERSECTION;
		playingFied_[coord.x][coord.y + 2].type = INTERSECTION;
		playingFied_[coord.x][coord.y - 2].type = INTERSECTION;
		playingFied_[coord.x + 2][coord.y - 2].type = INTERSECTION;
		playingFied_[coord.x - 2][coord.y + 2].type = INTERSECTION;

		playingFied_[coord.x - 1][coord.y - 1].type = EDGE;
		playingFied_[coord.x + 1][coord.y + 1].type = EDGE;
		playingFied_[coord.x + 1][coord.y - 2].type = EDGE;
		playingFied_[coord.x + 2][coord.y - 1].type = EDGE;
		playingFied_[coord.x - 1][coord.y + 2].type = EDGE;
		playingFied_[coord.x - 2][coord.y + 1].type = EDGE;
	}

	// for (int i = 0; i < FIELD_SIZE; ++i) {
	// 	for (int j = 0; j < FIELD_SIZE; ++j) {
	// 		if (!playingFied_[i][j]) {
	// 			playingFied_[i][j] = new BlankCell;
	// 		}			
	// 	}
	// }
}

void Board::deployment(DeploymentType type)
{
	// map<Resource, vector<Coordinates>> resourcesPlacement = {
	// 	{NOTHING, 	{ {10, 10} } },
	// 	{WOOD, 		{ { 4, 10}, {16,  4}, {10, 16}, { 8, 14} } },
	// 	{BRICKS, 	{ { 4, 16}, { 6, 12}, {12,  6} } }, 
	// 	{FLEECE, 	{ { 2, 14}, {18,  6}, {16, 10}, {12, 12} } }, 
	// 	{CORN, 		{ { 6, 18}, { 6,  6}, {10,  4}, {14, 14} } }, 
	// 	{ORE, 		{ {14,  2}, { 8,  8}, {14,  8} } }
	// };

	for (auto it_map = Settings::resourcesPlacement.begin(); it_map != Settings::resourcesPlacement.end(); ++it_map) 
	{
		for (auto it_vect = it_map->second.begin(); it_vect != it_map->second.end(); ++it_vect) 
		{
			(*this)[*it_vect].resource = it_map->first;
		}
	}
}

CellType Board::getCellType(Coordinates coord)
{
	return (*this)[coord].type;
}

void Board::playerInitDeployment(const Color col)
{	
	auto vect = Settings::init_pos[col];
	for (auto it_vect : vect)
	{
		Coordinates crd = it_vect;
		CellType type = getCellType(crd);
		if (type == INTERSECTION)
		{
			(*this)[crd].building = { SETTLEMENT, col };
		}
		else if (type == EDGE)
		{
			(*this)[crd].building = { ROAD, col };
		}
	}
}

Resource Board::getGexResource(Coordinates coord)
{
	Cell cell = (*this)[coord];

	if (cell.type != GEXAGON)
	{
		return NOTHING;
	}
	else
	{
		// auto gex = dynamic_cast<Gexagon*>(cell);
		return cell.resource;
	}
}

vector<Coordinates> Board::getGexesByNumber(const int num)
{
	return Settings::gex_numbers[num];
}

vector<Coordinates> Board::getEdgesByEdge(Coordinates coord)
{
	vector<Coordinates> answer;

	for (int i = -2; i < 3; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			int x = coord.x + i;
			int y = coord.y + j;
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = playingFied_[x][y];
				if (cell.type == EDGE)
				{
					answer.push_back({x, y});
				}
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
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = playingFied_[x][y];
				Cell cell_between = playingFied_[(x + coord.x) / 2][(y + coord.y) / 2];
				if (cell.type == INTERSECTION && cell_between.type == EDGE)
				{
					answer.push_back({x, y});
				}
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
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = playingFied_[x][y];
				if (cell.type == INTERSECTION)
				{
					answer.push_back({x, y});
				}
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
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = playingFied_[x][y];
				if (cell.type == EDGE)
				{
					answer.push_back({x, y});
				}
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
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = playingFied_[x][y];
				if (cell.type == INTERSECTION)
				{
					answer.push_back({x, y});
				}
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
	if ((*this)[coord].building.type != NO_BUILDING)
	{
		cout << "Can not build road in " << coord << endl;
		cout << (*this)[coord].building.type << " is here" << endl;
		return false;
	}

	vector<Coordinates> nearby_edges = getEdgesByEdge(coord);

	for (auto edge : nearby_edges)
	{
		if ((*this)[edge].building.color == color)
		{
			// cout << "Can build road in " << coord << endl;
			return true;
		}
	}

	cout << "Can not build road in " << coord << endl;
	cout << "No nearby roads" << endl;
	return false;
}

bool Board::canBuildSettlement(Color color, Coordinates coord)
{
	if ((*this)[coord].building.type != NO_BUILDING)
	{
		cout << "Can not build settlement in " << coord << endl;
		cout << (*this)[coord].building.type << " is here" << endl;
		return false;
	}

	vector<Coordinates> nearby_intersections = getIntersectionsByIntersection(coord);

	for (auto isect : nearby_intersections)
	{
		if ((*this)[isect].building.type != NO_BUILDING)
		{
			cout << "Can not build settlement in " << coord << endl;
			cout << (*this)[isect].building.type << " in " << isect << endl;
			return false;
		}
	}

	vector<Coordinates> nearby_edges = getEdgesByIntersection(coord);

	for (auto edge : nearby_edges)
	{
		if ((*this)[edge].building.color == color)
		{
			// cout << "Can build settlement in " << coord << endl;
			return true;
		}
	}

	cout << "Can not build settlement in " << coord << endl;
	cout << "No nearby roads" << endl;
	return false;
}

bool Board::canBuildCity(Color color, Coordinates coord)
{
	if ((*this)[coord].building.type != SETTLEMENT)
	{
		cout << "Can not build city in " << coord << endl;
		cout << (*this)[coord].building.type << " is here" << endl;
		return false;
	}

	// cout << "Can build city in {" << coord.x << ", " << coord.y << "}" << endl;
	return true;
}

bool Board::canBuild(BuildingType type, Color color, Coordinates coord)
{
	if (color == NO_COLOR)
	{
		cout << "Can not build in " << coord << endl;
		cout << "No color" << endl;
		return false;
	}

	if ((*this)[coord].type != BuildToCellType(type))
	{
		cout << "Can not build in " << coord << endl;
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
			cout << "Can not build in " << coord << endl;
			cout << "Default case" << endl;
			return false;
	}

	cout << "Can not build in " << coord << endl;
	cout << "End of function" << endl;
	return false;
}


// Cell* Board::operator[](Coordinates crd)
Cell& Board::operator[](Coordinates crd)
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
			} else if (j == -1) {
				if (i > 9)
					cout << i;
				else
					cout << " " << i;
			} else {
				int text_color = C_Reset;
				int city = 0;
				BuildingType type = playingFied_[i][j].building.type;
				if (type != NO_BUILDING)
				{
					if (type == CITY)
					{
						city = 1;
					}
					Color color = playingFied_[i][j].building.color;
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

				if (playingFied_[i][j].type == GEXAGON)
				{
					Cell gexagon = playingFied_[i][j];
					Resource res = gexagon.resource;
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

				switch (playingFied_[i][j].type) 
				{
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