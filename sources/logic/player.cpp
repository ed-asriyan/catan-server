#include "player.hpp"

Player::Player(Color col)
{
	color_ = col;
	totalResourcesAmount_ = 0;
	resourcesAmount_ = { 
		{WOOD, 0},
		{BRICKS, 0},
		{FLEECE, 0}, 
		{CORN, 0}, 
		{ORE, 0}
	};
}

Player::~Player()
{

}

Color Player::getColor()
{
	return color_;
}