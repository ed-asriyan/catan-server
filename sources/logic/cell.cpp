#include "cell.hpp"

Cell::Cell()
{
	type_ = BLANK_CELL;
	building = {NO_BUILDING, NO_COLOR};
}

Cell::~Cell() {}

CellType Cell::type()
{
	return type_;
}

BlankCell::BlankCell() {}

BlankCell::~BlankCell() {}

Gexagon::Gexagon() 
{
	type_ = GEXAGON;
	resource = NOTHING;
}

Gexagon::~Gexagon() {}

Intersection::Intersection()  
{
	type_ = INTERSECTION;
	harbor = {NO_HARBOR, NOTHING};
}

Intersection::~Intersection() {}

Edge::Edge() 
{
	type_ = EDGE;
}

Edge::~Edge() {} 