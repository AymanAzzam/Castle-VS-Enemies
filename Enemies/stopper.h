#pragma once
#include "Enemy.h"

class stopper_enemy : public Enemy
{
public:
	stopper_enemy(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp = 1);
	virtual void Move();
	virtual void Attack(int currenttime);
	~stopper_enemy(void);
	void calc_damage_effect_on_me(int currenttime);
};

