#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#define C_Reset      0
#define C_Bold       1
#define C_Under      2
#define C_Invers     3
#define C_Normal     4
#define C_Black      4
#define C_Red        5
#define C_Green      6
#define C_Brown      7
#define C_Blue       8
#define C_Magenta    9
#define C_Cyan       10
#define C_Light      11
#define N_COLORS     C_Light+1

static int tcolor [N_COLORS] = {
  0,  1,  4,  7, 30, 31, 
 32, 33, 34, 35, 36, 37 
};

#include <vector>
#include <array>
#include <map>
#include <iostream>

#include "sources.hpp"
#include "player.hpp"
#include "settings.hpp"

class Board;
#include "board_iterator.hpp"

using namespace std;

class Board
{
public:
	Board();
	~Board();

	CellType getCellType(Coordinates);
	void initialization();
	void deployment(DeploymentType type = DEFAULT);
	void playerInitDeployment(Color);
	Resource getGexResource(Coordinates);

	bool canBuildRoad(Color, Coordinates);
	bool canBuildSettlement(Color, Coordinates);
	bool canBuildCity(Color, Coordinates);
	bool canBuild(BuildingType, Color, Coordinates);
	void show();

	Cell& operator[](Coordinates);

private:
	array<array<Cell, FIELD_SIZE>, FIELD_SIZE> playingFied_;
};

#endif