#pragma once 
#include "Enemy.h"

class shielded :public Enemy
{
	double priority;
	static double C1, C2, C3;
	int remainingtimetoshoot;
public:
	shielded(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp = 1);
	virtual void Move();
	virtual void Attack(int currenttime);
	double get_priority() const;
	~shielded(void);
	void calc_damage_effect_on_me(int currenttime);
	bool isshielded() const;
	virtual bool operator>(const shielded & e) const;
	static void setConst(double c1, double c2, double c3);
	void cal_remaining_time(int currenttime);
	int	get_remaining_time_to_shoot() const;
};
