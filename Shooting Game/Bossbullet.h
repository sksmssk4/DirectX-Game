#pragma once
#include "entity.h"
#ifndef BOSSBULLET_H
#define BOSSBULLET_H

class Bossbullet:public entity{

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

