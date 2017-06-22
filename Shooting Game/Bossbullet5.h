#pragma once
#include "entity.h"
#ifndef BOSSBULLET5_H
#define BOSSBULLET5_H

class Bossbullet5 :public entity {

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
