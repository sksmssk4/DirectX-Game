#include "Hero.h"


enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//주인공 클래스 

bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

void Hero::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}

void Hero::hit_init(float x, float y)
{

	x_pos = x - 20.0f;
	y_pos = y;

}

void Hero::move(int i)
{

	switch (i)
	{
	case MOVE_UP:
		y_pos -= 8.0f;
		hit_Move = true;
		break;

	case MOVE_DOWN:
		y_pos += 8.0f;
		hit_Move = true;
		break;


	case MOVE_LEFT:
		x_pos -= 7.0f;
		hit_Move = true;
		break;


	case MOVE_RIGHT:
		x_pos += 7.0f;
		hit_Move = true;
		break;
	}
	if (x_pos < 0)
		x_pos = 0;
	if (y_pos < 0)
		y_pos = 0;
	if (y_pos > 380)
		y_pos = 380;
}
bool Hero::check_collision(float x, float y)
{

	//충돌 처리 시                             y   
	if (sphere_collision_check(x_pos, y_pos, 20.0f, x, y, 20.0f) == true)
	{
		hit_Show = true;
		return true;
	}
	else {
		return false;
	}
}

bool Hero::show()
{
	return hit_Show;
}

void Hero::hide()
{
	hit_Show = false;
}

void Hero::active()
{
	hit_Show = true;
}
