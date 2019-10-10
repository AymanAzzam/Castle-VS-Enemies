#include "virtual_enemy.h"
#include "../Castle/Tower.h"
virtual_enemy::virtual_enemy(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp)
{
	Clr = r_c;
	Region = r_region;
	SetDistance(MaxDistance);
	state = 1;
	set_ats(arrts);
	set_fp(ffpp);
	set_health(1);
	set_reloadtime(repe);
	set_speed(sp);
	firstshoot = 0;
	attackingtime = arrts;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void virtual_enemy::Move() {
	int sp = speed;
	while (tow->isPaved(Distance) && sp != 0) {
		DecrementDist();
		sp--;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void virtual_enemy::Attack(int currenttime) {
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
virtual_enemy::~virtual_enemy(void)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void virtual_enemy::calc_damage_effect_on_me(int currenttime) {
	Health-=(1.0/Distance)*tow->getFirePower()*(1/1);
	if(tow->getstop()){
		if(firstshoot==0){
			firstshoot=currenttime;
		}
	}
	if (Health <= 0.0) {
		killedtime = currenttime;
		state = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
