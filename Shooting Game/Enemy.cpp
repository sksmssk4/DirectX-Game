#include "Enemy.h"



void Enemy::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy::move()
{
	x_pos -= 3;

}
