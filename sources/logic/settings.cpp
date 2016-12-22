#include "settings.hpp"

int Settings::win_score = 10;

std::vector<Coordinates> Settings::gexCoordinates = {
	{ 6, 18}, { 4, 16}, { 2, 14}, 
	{ 4, 10}, { 6,  6}, {10,  4}, 
	{14,  2}, {16,  4}, {18,  6}, 
	{16, 10}, {14, 14}, {10, 16}, 
	{ 8, 14}, { 6, 12}, { 8,  8}, 
	{12,  6}, {14,  8}, {12, 12}, 
	{10, 10}
};

std::map<Resource, std::vector<Coordinates>> Settings::resourcesPlacement = {
	{NOTHING, 	{ {10, 10} } },
	{WOOD, 		{ { 4, 10}, {16,  4}, {10, 16}, { 8, 14} } },
	{BRICKS, 	{ { 4, 16}, { 6, 12}, {12,  6} } }, 
	{FLEECE, 	{ { 2, 14}, {18,  6}, {16, 10}, {12, 12} } }, 
	{CORN, 		{ { 6, 18}, { 6,  6}, {10,  4}, {14, 14} } }, 
	{ORE, 		{ {14,  2}, { 8,  8}, {14,  8} } }
};

std::map<int, std::vector<Coordinates>> Settings::gex_numbers = {
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

std::map<Color, std::vector<Coordinates>> Settings::init_pos = {
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

std::map<BuildingType, std::map<Resource, int>> Settings::costs = {
	{ NO_BUILDING, {} }, 
	{ SETTLEMENT, {
		{ WOOD, 1 }, { BRICKS, 1 }, { FLEECE, 1 }, { CORN, 1 }
	} },
	{ CITY , {
		{ CORN, 2 }, { ORE, 3 }
	} },
	{ ROAD, {
		{ WOOD, 1 }, { BRICKS, 1 }
	} }
};

std::map <Resource, int> Settings::init_resources = { 
	{WOOD, 		100},
	{BRICKS, 	100},
	{FLEECE, 	100}, 
	{CORN, 		100}, 
	{ORE, 		100}
};

