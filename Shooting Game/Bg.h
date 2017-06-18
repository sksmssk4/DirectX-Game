#pragma once

#include "entity.h"
#ifndef BG_H
#define BG_H

class Bg :public entity {
public:
	void init(float x, float y);
	void move();
};

#endif