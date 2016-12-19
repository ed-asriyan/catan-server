#include "player.hpp"

Player::Player()
{
	totalResourcesAmount_ = 0;
	resourcesAmount_ = { 
		{WOOD, 		100},
		{BRICKS, 	100},
		{FLEECE, 	100}, 
		{CORN, 		100}, 
		{ORE, 		100}
	};
}

Player::~Player()
{

}

void Player::addResource(Resource res, int num)
{
	resourcesAmount_[res] += num;
	totalResourcesAmount_ += num;
}

void Player::takeResource(Resource res, int num)
{
	if (haveResourse(res, num))
	{
		resourcesAmount_[res] -= num;
		totalResourcesAmount_ -= num;
	}
}

bool Player::haveResourse(Resource res, int num)
{
	if (resourcesAmount_[res] < num)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Player::show()
{
	cout << "WOOD  : " << resourcesAmount_[WOOD] 	<< endl;
	cout << "BRICKS: " << resourcesAmount_[BRICKS] 	<< endl;
	cout << "FLEECE: " << resourcesAmount_[FLEECE] 	<< endl;
	cout << "CORN:   " << resourcesAmount_[CORN] 	<< endl;
	cout << "ORE:    " << resourcesAmount_[ORE] 	<< endl;
}