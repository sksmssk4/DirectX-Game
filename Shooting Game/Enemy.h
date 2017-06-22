#pragma once

#include "entity.h"
#ifndef ENEMY_H
#define ENEMY_H


// 적 클래스 
class Enemy :public entity {

public:
	Enemy();
	void fire();
	void init(float x, float y);
	void move();

	bool death1 = false;
	bool death2 = false;
	bool death3 = false;

};

#endif
