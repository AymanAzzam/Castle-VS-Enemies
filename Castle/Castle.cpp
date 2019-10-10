#include "Castle.h"
#include "..\Battle.h"
#include "..\GUI\GUI.h"
#include "..\Enemies\Enemy.h"

Castle::Castle(Battle *battle)
{
	this->battle = battle;
	for (int i = 0; i < NoOfRegions; i++) {
		Towers[i].setRegion(static_cast<REGION> (i));
		Towers[i].setCastle(this);
	}
}

void Castle::setFile(File* pF) {
	pFile = pF;
}

void Castle::addEnemy(Enemy * enemy)
{
	inactive.push(enemy);
}

void Castle::step(int currentTime, MenuItem action)
{
	if (isKilled())
		return;
	for (int i = 0; i < NoOfRegions; i++) {
		if (Towers[i].isKilled()) {
			int x = i;
			while (Towers[x].isKilled())
				x = (x + 1) % NoOfRegions;
			Towers[x].moreEnemies(Towers[i]);
		}
	}
	while (!inactive.empty() && inactive.peek()->get_ats() <= currentTime) {
		Enemy* enemy = inactive.pop();
		int k = enemy->GetRegion();/*
		while (Towers[k].isKilled())
			k = (k + 1) % NoOfRegions;
		Towers[k].addEnemy(enemy);*/
		Tower* tower = &Towers[enemy->GetRegion()];
		while (tower->isKilled())
			tower = &Towers[(tower->getRegion() + 1) % NoOfRegions];
		tower->addEnemy(enemy);
		battle->AddEnemyToDraw(enemy);
	}
	for (int i = 0; i < NoOfRegions; i++) {
		Towers[i].step(currentTime, action);
	}

	tomb.flush(pFile);
}

void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
}

void Castle::setFirePower(double power)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].setFirePower(power);
	}
}

void Castle::setEnemyPerStep(int N)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].setEnemyPerStep(N);
	}
}

void Castle::killedEnemy(Enemy * enemy)
{
	tomb.push(enemy);
}

bool Castle::isKilled() const
{
	double health = 0;
	for (int i = 0; i < NoOfRegions; i++) {
		health += Towers[i].GetHealth();
	}
	return health == 0;
}

Queue<string> Castle::getInfo()
{
	Queue<string> info;
	for (int i = 0; i < NoOfRegions; i++) {
		Queue<string> infoTower = Towers[i].getInfo();
		while (!infoTower.empty()) {
			info.push(infoTower.pop());
		}
	}
	return info;
}

bool Castle::win() const
{
	if (inactive.empty()) {
		for (int i = 0; i < NoOfRegions; i++) {
			if (!Towers[i].emptyRegion())
				return false;
		}
		return true;
	}
	return false;
}

void Castle::getHealth(double& H1, double& H2, double& H3, double& H4) {
	H1 = Towers[0].GetHealth();
	H2 = Towers[1].GetHealth();
	H3 = Towers[2].GetHealth();
	H4 = Towers[3].GetHealth();
}

void Castle::getUnPaved(int & P1, int & P2, int & P3, int & P4)
{
	P1 = Towers[0].getUnPaved();
	P2 = Towers[1].getUnPaved();
	P3 = Towers[2].getUnPaved();
	P4 = Towers[3].getUnPaved();
}

void Castle::clear() {
	for (int i = 0; i < NoOfRegions; i++) {
		Towers[i].clear();
	}
	while (!inactive.empty()) {
		Enemy* tmp = inactive.pop();
		delete tmp;
	}
}

int Castle::getUnPavedDistance(REGION region) const
{
	return Towers[region].getUnPaved();
}
