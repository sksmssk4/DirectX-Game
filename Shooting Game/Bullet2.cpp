#include "Bullet2.h"

bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool Bullet2::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32.0f, x, y, 32.0f) == true)
	{
		hit_countt = hit_countt + 1; // 총알과 적이 충돌할 때마다 충돌횟수를 1씩 증가시킴
		bShow = false;
		return true;
	}
	else {

		return false;
	}
}


void Bullet2::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool Bullet2::show()
{
	return bShow;

}


void Bullet2::active()
{
	bShow = true;

}

void Bullet2::move()
{
	x_pos += 16;
	y_pos -= 10;
}

void Bullet2::hide()
{
	bShow = false;

}
