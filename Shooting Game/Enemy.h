#pragma once

#include "entity.h"
#ifndef ENEMY_H
#define ENEMY_H


// �� Ŭ���� 
class Enemy :public entity {

public:
	void fire();
	void init(float x, float y);
	void move();

};

#endif
