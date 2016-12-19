#pragma once

#include <map>
#include <vector>

#include "sources.hpp"

namespace Settings
{
	extern std::vector<Coordinates> gexCoordinates;
	
	extern std::map<Resource, std::vector<Coordinates>> resourcesPlacement;
	
	extern std::map<int, std::vector<Coordinates>> gex_numbers;
	
	extern std::map<Color, std::vector<Coordinates>> init_pos;
	
	extern std::map<BuildingType, std::map<Resource, int>> costs;
}
