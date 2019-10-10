#pragma once
#include "Enemies\Enemy.h"
#include "Data Structure\List.h"

class File;

class Tomb
{
	List<Enemy*> killed;
public:
	Tomb();
	~Tomb();
	void push(Enemy* enemy);
	void flush(File* pFile);
};

