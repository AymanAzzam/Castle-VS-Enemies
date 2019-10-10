#pragma once

#include "Tower.h"
#include "..\Data Structure\Queue.h"
#include "..\Tomb.h"

class Battle;

class Castle
{
private:
	Tower Towers[NoOfRegions];
	Queue<Enemy*> inactive; // Queue contains all inactive enemies
	Tomb tomb; // tomb of the castle. Every time step all killed enemies goes to tomb.
	Battle *battle;
	File* pFile;
public:

	Castle(Battle *battle);
	void setFile(File* pF);
	void addEnemy(Enemy *enemy); // add inactive enemy.
	void step(int currentTime, MenuItem action); // this function is called every time step.
	void SetTowersHealth(double h);
	void setFirePower(double power);
	void setEnemyPerStep(int N); // set number of enemies to shoot every time step.
	void killedEnemy(Enemy* enemy); // sends killed enemy to the tomb.
	bool isKilled() const;
	Queue<string> getInfo();
	bool win() const;
	void getHealth(double& H1, double& H2, double& H3, double& H4);
	void getUnPaved(int& P1, int& P2, int& P3, int& P4);
	void clear();
	int getUnPavedDistance(REGION region) const;
};
