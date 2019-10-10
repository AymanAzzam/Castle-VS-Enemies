#include "Battle.h"
#include "File.h"

Battle::Battle() : pFile(new File(this)), BCastle(this)
{
	pGUI = new GUI;
	EnemyCount = 0;
	BCastle.setFile(pFile);
}

MenuItem Battle::getAction() {
	MenuItem mi;
	do {
		pGUI->ClearStatusBar();
		pGUI->PrintMessage(18, "Choose an action from the menu bar."); //18 for the font
		mi = pGUI->getAction();
	} while (mi == Battle_Area);
	return mi;
}

void Battle::execute(MenuItem act) {
	int TH, N, TP, time = 0;
	Point p;
	pFile->read_name(pGUI); // reading the file name ( the status bar will be cleared with first writing in the status bar )
	pFile->TowerInfo(TH, N, TP);
	BCastle.SetTowersHealth(TH);
	BCastle.setEnemyPerStep(N);
	BCastle.setFirePower(TP);
	pFile->PrioConst();
	pFile->ReadEnemies();

	while (!BCastle.win() && !BCastle.isKilled()) {
		if (act == interactive_mode) {
			MenuItem a = pGUI->getAction();
			if (a == MENU_EXIT || a == interactive_mode || a == silent_mode || a == step_by_step_mode)
				throw a;
		}
		if (act == step_by_step_mode) {
			MenuItem a = pGUI->getAction(false);
			if (a == MENU_EXIT || a == interactive_mode || a == silent_mode || a == step_by_step_mode)
				throw a;
			Sleep(300);
		}
		++time;
		BCastle.step(time,act);
		if (act != silent_mode)
			draw();

	}

	double H1, H2, H3, H4;
	BCastle.getHealth(H1, H2, H3, H4);
	pFile->TotalDamage(TH - H1, TH - H2, TH - H3, TH - H4);
	int P1, P2, P3, P4;
	BCastle.getUnPaved(P1, P2, P3, P4);
	pFile->UnPavedDis(P1, P2, P3, P4);
	pGUI->ClearStatusBar();
	if(act == silent_mode)
		pGUI->PrintMessage(18, "Successfully reading file =)");
	if (BCastle.win())
	{
		pFile->Win(true);
		if (act != silent_mode)
		{
			pGUI->PrintMessage(18,"Congratulation ! Game is WIN");
			PlaySound("Sounds\\Ta Da-SoundBible.com-1884170640.wav",NULL,SND_FILENAME | SND_ASYNC);
		}
	}
	if (BCastle.isKilled() && !BCastle.win())
	{
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		pFile->Win(false);
		if (act != silent_mode)
		{
			pGUI->PrintMessage(18,"Loser ! Game is LOSS");
			PlaySound("Sounds\\fail-trombone-01.wav",NULL,SND_FILENAME | SND_ASYNC);
		}
	}
	Sleep(2000);
	clear();
}

void Battle::draw() {
	pGUI->ClearBattleArea();
	pGUI->drawPaved(&BCastle);
	pGUI->DrawCastle();
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
	//pFile->status_bar(pGUI, BCastle.getInfo());
	pGUI->PrintCastleInfo(BCastle.getInfo());
}

void Battle::addEnemy(Enemy* ptr) {
	BCastle.addEnemy(ptr);
}

void Battle::AddEnemyToDraw(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount)
		BEnemiesForDraw[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::clear() {
	pGUI->ClearBattleArea();
	pGUI->DrawCastle();
	BCastle.clear();
	pFile->clear();
	for (int i = 0; i < EnemyCount; ++i)
		delete BEnemiesForDraw[i];
	EnemyCount = 0;
}

Battle::~Battle()
{
	clear();
	delete pGUI;
	delete pFile;
}
