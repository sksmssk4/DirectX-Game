#pragma once

#include "entity.h"
#ifndef HERO_H
#define HERO_H

class Hero :public entity {

public:
	Hero();
	bool hit_Show;
	bool hit_Move = false;
	bool show();
	void hide();
	void active();

	void fire();
	void super_fire();
	void move(int i);
	void init(float x, float y);
	void hit_init(float x, float y);
	bool check_collision(float x, float y);
};

#endif
