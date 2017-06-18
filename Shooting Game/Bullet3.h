#pragma once

#include "entity.h"
#ifndef BULLET3_H
#define BULLET3_H

class Bullet3 :public entity {

public:

	int hit_counttt = 0; // 총알이 적과 충돌한 횟수
	bool bShow;
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);

};

#endif