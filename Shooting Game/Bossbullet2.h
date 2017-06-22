#pragma once
#include "entity.h"
#ifndef BOSSBULLET2_H
#define BOSSBULLET2_H

class Bossbullet2 :public entity {

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
