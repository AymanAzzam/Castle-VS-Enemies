#include "paver.h"
#include "../Castle/Tower.h"

paver::paver(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp)
{
	Clr = r_c;
	Region = r_region;
	SetDistance(MaxDistance);
	set_ats(arrts);
	set_fp(ffpp);
	set_health(h);
	set_reloadtime(repe);
	set_speed(sp);
	firstshoot = 0;
	attackingtime = arrts;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void paver::Move() {
	return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void paver::Attack(int currenttime) {
	int fp = firepower;
	if (attackingtime == currenttime) {
		while (tow->isPaved(Distance) && fp > 0) {
			DecrementDist();
			fp--;
		}
		while (fp != 0) {
			DecrementDist();
			tow->pave(1);
			fp--;
		}
		attackingtime += reloadperiod;
	}
	else {
		int sp = speed;
		while (tow->isPaved(Distance) && sp != 0) {
			DecrementDist();
			sp--;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
paver::~paver(void)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void paver::calc_damage_effect_on_me(int currenttime) {
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
			PlaySound("Sounds\\Hit.wav",NULL,SND_FILENAME | SND_ASYNC);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////