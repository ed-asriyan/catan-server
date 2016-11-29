#ifndef _SOURCES_HPP_
#define _SOURCES_HPP_ 

#define FIELD_SIZE 21
#define GEX_AMOUNT 19

enum Resource { NOTHING, WOOD, BRICKS, FLEECE, CORN, ORE };

enum CellType { BLANK_CELL, GEXAGON, INTERSECTION, EDGE };

enum Color { NO_COLOR, ORANGE, BLUE, WHITE, RED };

enum BuildingType { NO_BUILDING, SETTLEMENT, CITY, ROAD };

enum HarborType { NO_HARBOR, ORDINARY, SPECIAL };

enum DeploymentType { DEFAULT, RANDOM };

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