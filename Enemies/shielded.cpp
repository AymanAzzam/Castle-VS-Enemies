#include "shielded.h"
#include "../Castle/Tower.h"

shielded::shielded(color r_c, REGION r_region, int arrts, int ffpp, int repe, double h, int sp)
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
	remainingtimetoshoot = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void shielded::Move() {
	int sp = speed;
	while (tow->isPaved(Distance) && sp != 0) {
		DecrementDist();
		sp--;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void shielded::Attack(int currenttime) {
	if (attackingtime == currenttime) {
		damage = (2.0 / Distance)*firepower;
		tow->damage(damage);
		attackingtime += reloadperiod;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
double shielded::get_priority()const {
	return ((firepower / Distance)*C1 + (C2 / (get_remaining_time_to_shoot() + 1)) + (Health*C3));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
shielded::~shielded(void)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void shielded::calc_damage_effect_on_me(int currenttime) {
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
bool shielded::isshielded() const {
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool shielded:: operator> (const shielded & e) const {
		return get_priority() > e.get_priority() || (get_priority() == e.get_priority() && arrivaltimestamp < e.arrivaltimestamp);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
double shielded::C1 = 0;
double shielded::C2 = 0;
double shielded::C3 = 0;

void shielded::setConst(double c1, double c2, double c3) {
	C1 = c1;
	C2 = c2;
	C3 = c3;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void shielded::cal_remaining_time(int currenttime) {
	remainingtimetoshoot = attackingtime - currenttime - 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int shielded::get_remaining_time_to_shoot() const {
	return remainingtimetoshoot;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////