#include "Bossbullet2.h"



bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool Bossbullet2::check_collision(float x, float y)
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

void Bossbullet2::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool Bossbullet2::show()
{
	return bShow;

}


void Bossbullet2::active()
{
	bShow = true;

}

void Bossbullet2::move()
{
	x_pos -= 8;
	if (x_pos < 400)
	{
		x_pos += 7;
		if (x_pos < 380)
		{
			x_pos += 1;
			y_pos -= 8;
		}
	}
	if (y_pos < 100)
	{
		y_pos += 8;
		x_pos -= 8;
	}
		
}

void Bossbullet2::hide()
{
	bShow = false;

}
