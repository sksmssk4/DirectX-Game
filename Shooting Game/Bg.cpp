#include "Bg.h"



void Bg::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Bg::move()
{
	x_pos -= 10.0f;
	if (x_pos <= -840) x_pos = 840;
}