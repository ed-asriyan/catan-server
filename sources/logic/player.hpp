#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <map>
#include <iostream>

#include "sources.hpp"

using namespace std;

class Player
{
public:
	Player();
	// Player(Color col = NO_COLOR);
	~Player();

	int resourceAmount(Resource);
	int totalResourcesAmount();
	void addResource(Resource, int);
	void takeResource(Resource, int);
	bool haveResourse(Resource, int);
	// Color getColor();

	void show();

protected:
	map <Resource, int> resourcesAmount_;
	int totalResourcesAmount_;
	// Color color_;

};

#endif