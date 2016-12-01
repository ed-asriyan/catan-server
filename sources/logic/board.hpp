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

// fprintf (out,"\033[%dm",tcolor[color]);

#include <vector>
#include <array>
#include <map>
#include <iostream>

#include "sources.hpp"
#include "cell.hpp"
#include "player.hpp"

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

	vector<Coordinates> getGexesByNumber(int);
	vector<Coordinates> getIntersectionsByNumber(int);

	vector<Coordinates> getEdgesByEdge(Coordinates);
	vector<Coordinates> getIntersectionsByIntersection(Coordinates);	

	vector<Coordinates> getIntersectionsByGex(Coordinates);
	vector<Coordinates> getEdgesByGex(Coordinates);
	vector<Coordinates> getGexesByIntersection(Coordinates);
	vector<Coordinates> getEdgesByIntersection(Coordinates);
	vector<Coordinates> getIntersectionsByEdge(Coordinates);
	vector<Coordinates> getGexesByEdge(Coordinates);

	bool canBuildRoad(Color, Coordinates);
	bool canBuildSettlement(Color, Coordinates);
	bool canBuildCity(Color, Coordinates);
	bool canBuild(BuildingType, Color, Coordinates);
	void show();

	Cell* operator[](Coordinates);

private:

	// В порядке спирали против часовой стрелки
	// Согалсно правилам расстановки номеров
	const vector<Coordinates> gexagonCoordinates_ = {
		{ 6, 18}, { 4, 16}, { 2, 14}, 
		{ 4, 10}, { 6,  6}, {10,  4}, 
		{14,  2}, {16,  4}, {18,  6}, 
		{16, 10}, {14, 14}, {10, 16}, 
		{ 8, 14}, { 6, 12}, { 8,  8}, 
		{12,  6}, {14,  8}, {12, 12}, 
		{10, 10}
	};

	map<int, vector<Coordinates>> gex_numbers_ = {
		{ 2, { { 4, 16} } },
		{ 3, { {10, 16}, {12,  6} } },
		{ 4, { { 8, 14}, {10,  4} } },
		{ 5, { { 2, 14}, {12, 12} } },
		{ 6, { {14,  8}, { 6, 18} } },
		{ 7, { {10, 10} } },
		{ 8, { { 6,  6}, {14, 14} } },
		{ 9, { {18,  6}, { 6, 12} } },
		{10, { { 4, 10}, {16, 10} } },
		{11, { {14,  2}, { 8,  8} } },
		{12, { {16,  4} } }
	};

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

	array<array<Cell*, FIELD_SIZE>, FIELD_SIZE> playingFied_;
	// InitializeType init_type;

};

#endif