#pragma once

#include "entity.h"
#ifndef BULLET3_H
#define BULLET3_H

class Bullet3 :public entity {

public:

	int hit_counttt = 0; // �Ѿ��� ���� �浹�� Ƚ��
	bool bShow;
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);

};

#endif