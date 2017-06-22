#include "Bossbullet4.h"



bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool Bossbullet4::check_collision(float x, float y)
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

void Bossbullet4::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool Bossbullet4::show()
{
	return bShow;

}


void Bossbullet4::active()
{
	bShow = true;

}

void Bossbullet4::move()
{
	x_pos -= 8;
	if (x_pos < 400)
	{
		x_pos += 7;
		if (x_pos < 380)
		{
			x_pos += 1;
			y_pos += 9;
			if (y_pos > 380)
			{
				y_pos -= 9;
				x_pos -= 8;
			}
		}
	}
}

void Bossbullet4::hide()
{
	bShow = false;

}