#include "Enemy.h"
#include "..\Castle\Tower.h"

Enemy::Enemy() {}

Enemy::Enemy(color r_c, REGION r_region, int arrts, double ffpp, double repe, double h, int s)
{
	Clr = r_c;
	Region = r_region;
	SetDistance(MaxDistance);
	state = 1;
	set_ats(arrts);
	set_fp(ffpp);
	set_health(h);
	set_reloadtime(repe);
	attackingtime = 0;  //construct it with unlogic no.
	firstshoot = 0;
}

Enemy::~Enemy()
{
}

color Enemy::GetColor() const
{
	return Clr;
}

void Enemy::set_region(REGION r) {
	Region = r;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::thestate(int currenttime) {
	if (arrivaltimestamp == currenttime) {
		state = 2;
		attackingtime = arrivaltimestamp;
	}
}

int Enemy::get_state() const {
	return state;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}
//////////////////////////////////////////
void Enemy::set_ats(int a) {
	arrivaltimestamp = a;
}
int Enemy::get_ats()const {
	return arrivaltimestamp;
}
///////////////////////////////////////////////
void Enemy::set_fp(double a) {
	firepower = a;
}
double Enemy::get_fp()const {
	return firepower;
}
//////////////////////////////////////////////////////
void Enemy::set_health(double h) {
	Health = h;
}
double Enemy::get_health() const {
	return Health;
}
///////////////////////////////////////////////////
void Enemy::set_reloadtime(int r) {
	reloadperiod = r;
}
int Enemy::get_reloadtime() const {
	return reloadperiod;
}
///////////////////////////////////////////////////
void Enemy::set_speed(double sp) {
	speed = sp;
}

double Enemy::get_speed()const {
	return speed;
}
//////////////////////////////////////////////////
int Enemy::getfirstshootdelay() const {
	return (firstshoot - arrivaltimestamp);
}
//////////////////////////////////////////////////
int Enemy::killdelay() const {
	return (killedtime - firstshoot);
}
///////////////////////////////////////////
int Enemy::lifetime() const {
	return (killedtime - arrivaltimestamp);
}
///////////////////////////////////////////
bool Enemy::isshielded() const {
	return false;
}
///////////////////////////////////////////
double Enemy::get_damage() const {
	return damage;
}
//////////////////////////////////////////////
bool Enemy::iskilled() const {
	return(state == 0);
}
/////////////////////////////////////////////
double Enemy::get_priority() const {
	return 0;
}
/////////////////////////////////////////////
bool Enemy:: operator < (const Enemy & e) const {
	if (!iskilled())
		return arrivaltimestamp < e.arrivaltimestamp;
	return getfirstshootdelay() < e.getfirstshootdelay();
}
/////////////////////////////////////////////
bool Enemy:: operator > (const Enemy & e) const {
	if (!iskilled())
		return arrivaltimestamp > e.arrivaltimestamp;
	return getfirstshootdelay() > e.getfirstshootdelay();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::set_tower(Tower * t) {
	tow = t;
	Region = t->getRegion();
}
/////////////////////////////////////////////
void Enemy::step(int currenttime, MenuItem action) {
	ACT=action;
	Move();
	Attack(currenttime);
	cal_remaining_time(currenttime);
}
////////////////////////////////////////////////
void Enemy::treatment(double damage) {
	Health += damage;
}
//////////////////////////////////////////////////////////////////////
int Enemy::killed_time_step() const {
	return killedtime;
}
/////////////////////////////////////////////////////////////////////////
int Enemy::getID() const {
	return ID;
}
/////////////////////////////////////////////////////////////////////////
void Enemy::setID(int id) {
	ID = id;
}
///////////////////////////////////////////////////////////////////////////
void Enemy::cal_remaining_time(int currenttime) {
	return;
}
//////////////////////////////////////////////////////////////////////////