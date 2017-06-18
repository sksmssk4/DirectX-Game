#pragma once

#include "entity.h"
#ifndef SCORE_H
#define SCORE_H

class Score :public entity {
public:
	bool score0_show = true;
	bool score1_show = false;
	bool score2_show = false;
	bool score3_show = false;
	bool score4_show = false;
	bool score5_show = false;

	void init(float x, float y);
};

#endif