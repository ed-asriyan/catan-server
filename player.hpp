#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <map>

#include "sources.hpp"

using namespace std;

class Player
{
public:
	Player();
	~Player();

	int resourceAmount(Resource);
	int totalResourcesAmount();

protected:
	map <Resource, int> resourcesAmount_;
	int totalResourcesAmount_;

};

#endif