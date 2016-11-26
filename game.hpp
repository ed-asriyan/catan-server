#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <array>
#include <vector>
#include <map>
#include <iostream>

#include "cell.hpp"

#define FIELD_SIZE 21
#define GEX_AMOUNT 19

class Game
{
public:
	Game();
	Game(int gameID);
	~Game();

	int getID();
	void showTypes();
	CellType getCellType(Coordinates);
	int playersAmount();
	void deployment();
	
private:
	void initialization();
	// void deployment();

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
	int gameID_;
	int playersAmount_;
	

};

#endif