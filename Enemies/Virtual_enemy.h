#pragma once
#include "Enemy.h"
class virtual_enemy : public Enemy
{
public:
	virtual_enemy(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp = 0);
	virtual void Move();
	virtual void Attack(int currenttime);
	~virtual_enemy(void);
	void calc_damage_effect_on_me(int currenttime);
};

