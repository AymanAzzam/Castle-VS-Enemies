#pragma once
#include"Enemy.h"

class doctor : public Enemy
{
public:
	doctor(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp);
	virtual void Move();
	virtual void Attack(int currenttime);
	void set_mid(double);
	double get_midicine() const;  //will be added to the firepower of the other enemies whose power decreased
	~doctor(void);
	void calc_damage_effect_on_me(int currenttime);
};
