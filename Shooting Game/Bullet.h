#pragma once

#include "entity.h"
#ifndef BULLET_H
#define BULLET_H

// 총알 클래스 
class Bullet :public entity {

public:

	int hit_count = 0; // 총알이 적과 충돌한 횟수
	bool bShow;
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);

};

#endif
