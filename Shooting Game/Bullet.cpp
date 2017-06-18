#include "Bullet.h"

bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool Bullet::check_collision(float x, float y)
{
	//�浹 ó�� �� 
	if (sphere_collision_check(x_pos, y_pos, 32.0f, x, y, 32.0f) == true)
	{
		hit_count = hit_count + 1; // �Ѿ˰� ���� �浹�� ������ �浹Ƚ���� 1�� ������Ŵ
		bShow = false;
		return true;
	}
	else {

		return false;
	}
}


void Bullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}

bool Bullet::show()
{
	return bShow;

}


void Bullet::active()
{
	bShow = true;

}

void Bullet::move()
{
	x_pos += 16;
}

void Bullet::hide()
{
	bShow = false;

}
