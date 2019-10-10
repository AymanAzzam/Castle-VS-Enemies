#pragma once
#include "Castle\Castle.h"
//#include "File.h"

// it is the controller of the project

class File;
class GUI;

class Battle
{
private:
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
											// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	GUI* pGUI;
	File* pFile;

public:

	Battle();
	void draw();
	void addEnemy(Enemy* ptr);
	void AddEnemyToDraw(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();
	void execute(MenuItem act);
	MenuItem getAction();
	void clear();
	~Battle();
};

