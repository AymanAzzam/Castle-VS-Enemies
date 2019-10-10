#pragma once
#include "Enemy.h"

class fighter : public Enemy
{
public:
	fighter(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp = 1);
	virtual void Move();
	virtual void Attack(int currenttime);
	~fighter(void);
	void calc_damage_effect_on_me(int currenttime);
};

