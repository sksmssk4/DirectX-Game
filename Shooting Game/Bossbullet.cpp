#include "Bossbullet.h"



bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool Bossbullet::check_collision(float x, float y)
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

void Bossbullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool Bossbullet::show()
{
	return bShow;

}


void Bossbullet::active()
{
	bShow = true;

}

void Bossbullet::move()
{
	x_pos -= 10;
	if (x_pos < 500)
	{
		y_pos -= 10;
		if (x_pos < 250)
			y_pos += 20;
	}
}	

void Bossbullet::hide()
{
	bShow = false;

}