#pragma once
#include "entity.h"
#ifndef  EBULLTE_H
#define EBULLET_H

class eBullet:public entity {

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