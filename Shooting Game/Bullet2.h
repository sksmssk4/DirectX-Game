#pragma once

#include "entity.h"
#ifndef BULLET2_H
#define BULLET2_H

class Bullet2 :public entity {

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

