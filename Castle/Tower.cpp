#include "Tower.h"
#include "Castle.h"
#include "../Enemies/Enemy.h"
#include <string>
#include <climits>


Tower::Tower()
{
	Health = 0;
	unPaved = 30;
	enemyPerStep = 0;
	killed = 0;
	castle = NULL;
	stop=1;
}

void Tower:: set_stop(int s){
	stop=s;
}

int Tower:: getstop() const{
	return stop;
}

void Tower::step(int currentTime, MenuItem action)
{
	ACT=action;
	// Shooooooooot enemies !!!!
	shielded.sort(false);
	int i = 0;
	shielded.begin();
	while (i < enemyPerStep && !shielded.end()) {
		Enemy* enemy = shielded.get();
		if (stop == 0)
			stop = 1;
		else
			enemy->calc_damage_effect_on_me(currentTime);
		if (enemy->iskilled()) {
			shielded.pop();
			++killed;
			castle->killedEnemy(enemy);
		}
		else
			++shielded;
		++i;
	}
	otherActive.begin();
	while (i < enemyPerStep && !otherActive.end()) {
		Enemy* enemy = otherActive.get();
		if (stop == 0)
			stop = 1;
		else
			enemy->calc_damage_effect_on_me(currentTime);
		if (enemy->iskilled()) {
			otherActive.pop();
			++killed;
			castle->killedEnemy(enemy);
		}
		else
			++otherActive;
		++i;
	}
	// Enemies: It's our turn
	for (shielded.begin(); !shielded.end(); shielded++)
		shielded.get()->step(currentTime, action);
	for (otherActive.begin(); !otherActive.end(); otherActive++)
		otherActive.get()->step(currentTime, action);

}

void Tower::setEnemyPerStep(int N)
{
	enemyPerStep = N > 0 ? N : 1;
}

void Tower::addEnemy(Enemy * enemy)
{
	if (isKilled())
		return;
	enemy->set_tower(this);
	if (enemy->isshielded()) {
		shielded.push(enemy);
	}
	else {
		otherActive.push(enemy);
	}
}

int Tower::getUnPaved() const
{
	return unPaved;
}

void Tower::pave(int steps)
{
	unPaved -= steps;
	if (unPaved < MinDistance) unPaved = MinDistance;
}

bool Tower::isKilled() const
{
	return Health <= 0;
}

void Tower::damage(double amount)
{
	if(Health!=0)
	{
		Health -= amount;
		Health = Health < 0 ? 0 : Health;
		if(Health==0){
			if(ACT != silent_mode)
				PlaySound("Sounds\\bomb-02.wav",NULL,SND_FILENAME | SND_SYNC);
		}
	}
}

void Tower::setFirePower(int power)
{
	firePower = power;
}

int Tower::getFirePower() 
{
	if(stop==1){
		return firePower;}
	else{
		stop=1;
		return 0;
	}
}

void Tower::setRegion(REGION region)
{
	this->region = region;
}

REGION Tower::getRegion() const
{
	return region;
}

void Tower::moreEnemies(Tower & tower)
{
	for (tower.shielded.begin(); !tower.shielded.end(); tower.shielded++) {
		Enemy *enemy = tower.shielded.get();
		enemy->set_region(region);
		enemy->set_tower(this);
		if (!isPaved(enemy->GetDistance())) {
			enemy->SetDistance(unPaved + 1);
		}
	}
	for (tower.otherActive.begin(); !tower.otherActive.end(); tower.otherActive++) {
		Enemy *enemy = tower.otherActive.get();
		enemy->set_region(region);
		enemy->set_tower(this);
		if (!isPaved(enemy->GetDistance())) {
			enemy->SetDistance(unPaved + 1);
		}

	}
	shielded.append(tower.shielded);
	otherActive.merge(tower.otherActive);
}

void Tower::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return Health;
}

bool Tower::isPaved(int d)
{
	return d > unPaved;
}

Queue<string> Tower::getInfo()
{
	Queue<string> info;
	int total = shielded.getSize() + otherActive.getSize();
	string s ;
	s.push_back(getRegionChar());
	s += "  Health = " + to_string((int)Health) + ", Total active = " + to_string(total) + ", Killed = " + to_string(killed) + ", Unpaved = " + to_string(unPaved);
	info.push(s);
	shielded.begin();
	otherActive.begin();
	int j = 0;
	while (!shielded.end() || !otherActive.end()) {
		j = 0;
		s = "";
		for (; !shielded.end() && j < MAXPRINT; shielded++) {
			Enemy *enemy = shielded.get();
			s += "e" + to_string(enemy->getID()) + "(" + to_string(enemy->get_ats()) + ", " + to_string((int)enemy->get_health()) + "), ";
			j++;
		}
		for (; !otherActive.end() && j < MAXPRINT; otherActive++) {
			Enemy *enemy = otherActive.get();
			s += "e" + to_string(enemy->getID()) + "(" + to_string(enemy->get_ats()) + ", " + to_string((int)enemy->get_health()) + "), ";
			j++;
		}
		if (!s.empty()) {
			s.pop_back();
			s.pop_back();
			info.push(s);
		}
	}
	return info;
}

void Tower::setCastle(Castle * castle)
{
	this->castle = castle;
}

char Tower::getRegionChar() const
{
	return 'A' + region;
}

bool Tower::emptyRegion() const
{
	return (shielded.getSize() + otherActive.getSize()) == 0;
}

void Tower::cure(int firePower) {
	if(shielded.getSize() == 0 && otherActive.getSize() == 0) return;
	int min = INT_MAX;
	Enemy* minEnemy;
	for(shielded.begin();!shielded.end();shielded++) {
		Enemy* enemy = shielded.get();
		if (enemy->get_health() < min) {
			min = enemy->get_health();
			minEnemy = enemy;
		}
	}
	for(otherActive.begin();!otherActive.end();otherActive++) {
		Enemy* enemy = otherActive.get();
		if (enemy->get_health() < min) {
			min = enemy->get_health();
			minEnemy = enemy;
		}
	}
	minEnemy->set_health(minEnemy->get_health() + firePower);
}

void Tower::clear() {
	shielded.begin();
	while (shielded.getSize()) {
		Enemy* tmp = shielded.pop();
	}
	otherActive.begin();
	while (otherActive.getSize()) {
		Enemy* tmp = otherActive.pop();
	}
	unPaved = 30;
	killed = 0;
}
