#pragma once
#include "../Enemies/Enemy.h"
#include "../Data Structure/List.h"
#include "../Data Structure/Queue.h"
//#include "Castle.h"
using namespace std;

class Castle;

class Tower
{
	Castle* castle;
	double Health;
	int firePower;
	int enemyPerStep; // enemies to shoot every time step.
	int unPaved; // unpaved distance.
	List<Enemy*> shielded; // list of active shielded enemies in tower's region.
	List<Enemy*> otherActive; // list of all active non-shielded enemies int tower's region
	REGION region;
	int killed; // number of killed enemies
	MenuItem ACT;

	int stop;
public:
	Tower();
	void step(int currentTime, MenuItem action);
	void setEnemyPerStep(int N);
	void addEnemy(Enemy *enemy);
	int getUnPaved() const;
	void pave(int steps);
	bool isKilled() const;
	void damage(double amount);
	void setFirePower(int power);
	int getFirePower() ;
	void setRegion(REGION region);
	REGION getRegion() const;
	void moreEnemies(Tower &tower);
	void SetHealth(double h);
	double GetHealth() const;
	bool isPaved(int d);
	Queue<string> getInfo();
	void setCastle(Castle * castle);
	char getRegionChar() const;
	bool emptyRegion() const;
	void clear();
	void set_stop(int s);
	void cure(int firePower);
	int getstop() const;
};

