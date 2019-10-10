#include "doctor.h"
#include "../Castle/Tower.h"
#include "../Battle.h"

doctor::doctor(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp)
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
	attackingtime = arrts;
	firstshoot = 0;
}
void doctor:: Move(){
	int sp=speed;
	while(tow->isPaved(Distance) && sp != 0){ 
		DecrementDist();
		sp--;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void doctor:: Attack(int currenttime){   //damage here to cure
	if(attackingtime==currenttime){
		damage=(1.0/Distance)*firepower;
		tow->cure(damage);
		attackingtime+=reloadperiod;}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
doctor::~doctor(void)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void doctor:: calc_damage_effect_on_me(int currenttime){
	Health-=(1.0/Distance)*tow->getFirePower()*(1/1);
	if(tow->getstop()){
		if(firstshoot==0){
			firstshoot=currenttime;
		}
	}
	if(Health<=0.0){
		killedtime=currenttime;
		state=0;
		if(ACT != silent_mode)
			PlaySound("Sounds\\Hit.wav",NULL, SND_FILENAME | SND_ASYNC);
		//PlaySound(NULL,NULL,0);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////