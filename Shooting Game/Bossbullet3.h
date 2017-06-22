#pragma once
#include "entity.h"
#ifndef BOSSBULLET3_H
#define BOSSBULLET3_H

class Bossbullet3 :public entity {

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