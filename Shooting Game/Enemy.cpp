#include "Enemy.h"



void Enemy::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy::move()
{
	x_pos -= 5;
	if (y_pos < 0)
		y_pos = 0;
	if (y_pos > 380)
		y_pos = 380;

}
