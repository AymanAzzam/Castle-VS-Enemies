#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Enemies\paver.h"
#include "Enemies\doctor.h"
#include "Enemies\fighter.h"
#include "Enemies\shielded.h"
#include "Enemies\stopper.h"
#include "Enemies\Virtual_enemy.h"
#include "Data Structure\Queue.h"
#include "Data Structure\List.h"
#include "GUI\GUI.h"
using namespace std;

class Battle;

class File
{
	ifstream input;
	ofstream output;
	string name;
	int Killed, Total;
	int AllFD, AllKD;
	Battle* pBattle;
public:
	File(Battle* pB);
	void TowerInfo(int&, int&, int&);
	void PrioConst();
	void ReadEnemies();
	void PrintEnemies(List<Enemy*>&);
	void TotalDamage(double, double, double, double);
	void UnPavedDis(int&, int&, int&, int&);
	void Win(bool);
	//void status_bar(GUI*, Queue<string>&);
	void read_name(GUI*);
	void clear();
};