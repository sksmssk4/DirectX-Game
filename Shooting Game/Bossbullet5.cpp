#include "Bossbullet5.h"



bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool Bossbullet5::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 10.0f, x, y, 10.0f) == true)
	{
		bShow = false;
		return true;
	}
	else {

		return false;
	}
}

void Bossbullet5::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool Bossbullet5::show()
{
	return bShow;

}


void Bossbullet5::active()
{
	bShow = true;

}

void Bossbullet5::move()
{
	x_pos -= 10;
	if (x_pos < 500)
	{
		y_pos += 10;
		if (x_pos < 250)
			y_pos -= 20;
	}
}

void Bossbullet5::hide()
{
	bShow = false;

}
