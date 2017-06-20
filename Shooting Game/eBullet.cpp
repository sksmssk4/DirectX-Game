#include "eBullet.h"

bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool eBullet::check_collision(float x, float y)
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


void eBullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool eBullet::show()
{
	return bShow;

}


void eBullet::active()
{
	bShow = true;

}

void eBullet::move()
{
	x_pos -= 8;
}

void eBullet::hide()
{
	bShow = false;

}