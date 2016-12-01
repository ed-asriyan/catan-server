#include "sources.hpp"

CellType BuildToCellType(BuildingType type)
{
	switch (type)
	{
		case NO_BUILDING:
			return BLANK_CELL;
		case SETTLEMENT:
			return INTERSECTION;
		case CITY:
			return INTERSECTION;
		case ROAD:
			return EDGE;
	}

	return BLANK_CELL;
}

ostream& operator <<(ostream& os, const Coordinates& crd)
{
	os << "{" << crd.x << ", " << crd.y << "}";
	return os;
}

ostream& operator <<(ostream& os, const BuildingType& type)
{
	switch (type)
	{
		case NO_BUILDING:
			os << "NO_BUILDING";
			break;
		case ROAD:
			os << "ROAD";
			break;
		case SETTLEMENT:
			os << "SETTLEMENT";
			break;
		case CITY:
			os << "CITY";
			break;
	}

	return os;
}

// ostream& operator <<(ostream& os, const Resource& res)
// {

// }

ostream& operator <<(ostream& os, const Color& color)
{
	switch (color)
	{
		case ORANGE:
			os << "ORANGE";
			break;
		case BLUE:
			os << "BLUE";
			break;
		case WHITE:
			os << "WHITE";
			break;
		case RED:
			os << "RED";
			break;
		case NO_COLOR:
			os << "NO_COLOR";
			break;
	}

	return os;
}

// ostream& operator <<(ostream& os, const CellType& type)
// {

// }