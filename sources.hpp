#ifndef _SOURCES_HPP_
#define _SOURCES_HPP_ 

enum Resource { NOTHING, WOOD, BRICKS, FLEECE, CORN, ORE };

enum CellType { BLANK_CELL, GEXAGON, INTERSECTION, EDGE };

enum Color { NO_COLOR, ORANGE, BLUE, WHITE, RED };

enum BuildingType { NO_BUILDING, SETTLEMENT, CITY, ROAD };

enum HarborType { NO_HARBOR, ORDINARY, SPECIAL };

struct Coordinates {
	int x;
	int y;
};

struct Harbor
{
	HarborType type;
	Resource resource;
};

struct Building
{
	BuildingType type;
	Color color;
};

#endif