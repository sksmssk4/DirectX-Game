#pragma once

#include "entity.h"
#ifndef BULLET_H
#define BULLET_H

// �Ѿ� Ŭ���� 
class Bullet :public entity {

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
