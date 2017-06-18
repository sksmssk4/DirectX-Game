#include "Bullet3.h"

bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool Bullet3::check_collision(float x, float y)
{
	//�浹 ó�� �� 
	if (sphere_collision_check(x_pos, y_pos, 32.0f, x, y, 32.0f) == true)
	{
		hit_counttt = hit_counttt + 1; // �Ѿ˰� ���� �浹�� ������ �浹Ƚ���� 1�� ������Ŵ
		bShow = false;
		return true;
	}
	else {

		return false;
	}
}


void Bullet3::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool Bullet3::show()
{
	return bShow;

}


void Bullet3::active()
{
	bShow = true;

}

void Bullet3::move()
{
	x_pos += 16;
	y_pos += 10;
}

void Bullet3::hide()
{
	bShow = false;

}