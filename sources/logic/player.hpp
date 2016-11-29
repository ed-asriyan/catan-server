#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <map>

#include "sources.hpp"

using namespace std;

class Player
{
public:
	// Player();
	Player(Color col = NO_COLOR);
	~Player();

	int resourceAmount(Resource);
	int totalResourcesAmount();
	Color getColor();

protected:
	map <Resource, int> resourcesAmount_;
	int totalResourcesAmount_;
	Color color_;

};

#endif