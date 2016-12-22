#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <map>
#include <iostream>

#include "sources.hpp"
#include "settings.hpp"

using namespace std;

class Player
{
public:
	Player();
	~Player();

	int resourceAmount(Resource);
	int totalResourcesAmount();
	void addResource(Resource, int);
	void takeResource(Resource, int);
	bool haveResourse(Resource, int);
	void addScore(int);
	int getScore();

	void show();

protected:
	map <Resource, int> resourcesAmount_;
	int totalResourcesAmount_;
	int score_;
};

#endif