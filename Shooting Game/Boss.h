#pragma once
#include "entity.h"
#ifndef BOSS_H
#define BOSS_H

class Boss:public entity{

public:
	Boss();
	bool boss_show = false;
	bool hit_Show;
	bool hit_Move = false;
	bool show();
	void hide();
	void active();

	void move();
	void init(float x, float y);
	bool check_collision(float x, float y);
};

#endif

