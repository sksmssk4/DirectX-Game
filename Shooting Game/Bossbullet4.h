#pragma once
#include "entity.h"
#ifndef BOSSBULLET4_H
#define BOSSBULLET4_H

class Bossbullet4 :public entity {

public:
	bool bShow;
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
};

#endif

