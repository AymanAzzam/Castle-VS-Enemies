#include "Tomb.h"
#include "File.h"


Tomb::Tomb()
{
}


Tomb::~Tomb()
{
}

void Tomb::push(Enemy * enemy)
{
	killed.push(enemy);
}

void Tomb::flush(File* pFile)
{
	killed.sort(); // FD
	pFile->PrintEnemies(killed);
	killed.clear();
}
