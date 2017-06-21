#pragma once
#include "entity.h"
#ifndef SCORE2_H
#define SCORE2_H

class Score2 :public entity {
public:
	bool score0_show = true;
	bool score1_show = false;
	bool score2_show = false;
	bool score3_show = false;
	bool score4_show = false;
	bool score5_show = false;
	bool score6_show = false;
	bool score7_show = false;
	bool score8_show = false;
	bool score9_show = false;

	void init(float x, float y);
};

#endif

