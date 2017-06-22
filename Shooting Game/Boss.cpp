#include "Boss.h"


bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

Boss::Boss()
{
	HP = 1000;
}

void Boss::init(float x, float y)
{

	x_pos = x;
	y_pos = y;
}

void Boss::move()
{
	x_pos -= 2;
	if (x_pos == 550)
		x_pos += 2;
}
bool Boss::check_collision(float x, float y)
{
	if(sphere_collision_check(x_pos, y_pos, 100.0f, x, y, 100.0f) == true)
	{
		hit_Show = true;
		return true;
	}
	else {
		return false;
	}
}

bool Boss::show()
{
	return hit_Show;
}

void Boss::hide()
{
	hit_Show = false;
}

void Boss::active()
{
	hit_Show = true;
}
