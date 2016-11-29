#ifndef _BOARD_HPP_
#define _BOARD_HPP_

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

private:

	// В порядке спирали против часовой стрелки
	// Согалсно правилам расстановки номеров
	const vector<Coordinates> gexagonCoordinates_ = {
		{6, 18}, {4, 16}, {2, 14}, 
		{4, 10}, {6, 6}, {10, 4}, 
		{14, 2}, {16, 4}, {18, 6}, 
		{16, 10}, {14, 14}, {10, 16}, 
		{8, 14}, {6, 12}, {8, 8}, 
		{12, 6}, {14, 8}, {12, 12}, 
		{10, 10}
	};

	array<array<Cell*, FIELD_SIZE>, FIELD_SIZE> playingFied_;
	// InitializeType init_type;

};

#endif