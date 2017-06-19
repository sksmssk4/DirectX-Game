#pragma once

#include "entity.h"
#ifndef BULLET3_H
#define BULLET3_H

class Bullet3 :public entity {

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