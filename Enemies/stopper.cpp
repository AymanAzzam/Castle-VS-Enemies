#include "stopper.h"
#include "..\Castle\Tower.h"
#include "..\Battle.h"

stopper_enemy::stopper_enemy(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp)
{
	Clr = r_c;
	Region = r_region;
	SetDistance(MaxDistance);
	state = 1;
	set_ats(arrts);
	set_fp(ffpp);
	set_health(h);
	set_reloadtime(repe);
	set_speed(sp);
	firstshoot = 0;
	attackingtime = arrts;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void stopper_enemy::Move() {
	int sp = speed;
	while (tow->isPaved(Distance) && sp != 0) {
		DecrementDist();
		sp--;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stopper_enemy::Attack(int currenttime) {
	if (attackingtime == currenttime) {
		tow->set_stop(0);
		attackingtime += reloadperiod;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
stopper_enemy::~stopper_enemy(void)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void stopper_enemy::calc_damage_effect_on_me(int currenttime) {
	Health -= (1.0 / Distance)*tow->getFirePower()*(1 / 1);
	if(tow->getstop()){
		if(firstshoot==0){
			firstshoot=currenttime;
		}
	}
	if (Health <= 0.0) {
		killedtime = currenttime;
		state = 0;
		if(ACT != silent_mode)
			PlaySound("Sounds\\Hit.wav",NULL, SND_FILENAME | SND_ASYNC);
		//PlaySound(NULL,NULL,0);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
