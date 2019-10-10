#include "File.h"
#include "Battle.h"
#include <iomanip>

File::File(Battle* pB)
{
	pBattle = pB;
	Killed = AllFD = AllKD = Total = 0;
}

void File::read_name(GUI*pGUI)
{
	string arr;
	pGUI->ClearStatusBar();
	pGUI->PrintMessage(18, "Enter input file name : ");
	arr = pGUI->GetString();
	input.open(arr + ".txt");
	pGUI->ClearStatusBar();
	while (!input.is_open())
	{
		pGUI->PrintMessage(18, "Invalid File : Try again");
		Sleep(1000);
		pGUI->ClearStatusBar();
		pGUI->PrintMessage(18, "Enter input file name : ");
		arr = pGUI->GetString();
		input.open(arr + ".txt");
		pGUI->ClearStatusBar();
	}
	name=arr;
	pGUI->PrintMessage(18, "Successfully reading file =)");
	pGUI->PrintMessage(18,"Press mouse click",20);
}

void File::TowerInfo(int &TH, int &N, int &TP)
{
	input >> TH >> N >> TP;
}

void File::PrioConst()
{
	double C1, C2, C3;
	input >> C1 >> C2 >> C3;
	shielded::setConst(C1, C2, C3);
}

void File::ReadEnemies()
{
	int ID, TYP, RLD, T, POW,Speed;
	double H;
	char R;
	Enemy* e;
	input >> ID;
	while (ID != -1)
	{
		Total++;
		input >> TYP >> T >> H >> POW >> RLD >> R>>Speed;
		if (TYP == 0)
		{
			e = new paver(CYAN, static_cast<REGION>(R - 'A'), T, POW, RLD, H,Speed);
			e->setID(ID);
		}
		else if (TYP == 1)
		{
			e = new fighter(LAWNGREEN, static_cast<REGION>(R - 'A'), T, POW, RLD, H,Speed);
			e->setID(ID);
		}
		else if (TYP == 2)
		{
			e = new shielded(ORANGERED, static_cast<REGION>(R - 'A'), T, POW, RLD, H,Speed);
			e->setID(ID);
		}

		else if(TYP == 3)
		{
			e=new doctor(WHITE, static_cast<REGION>(R - 'A'),T,POW,RLD,H,Speed);  
			e->setID(ID);
		}
		
		else if(TYP == 4)
		{
			e=new stopper_enemy(YELLOW, static_cast<REGION>(R - 'A'),T,POW,RLD,H,Speed);  
			e->setID(ID);
		}
		
		else if(TYP == 5)
		{
			e=new virtual_enemy(DARKSLATEGRAY, static_cast<REGION>(R - 'A'),T,POW,RLD,H,Speed);  
			e->setID(ID);
		}
		pBattle->addEnemy(e);
		input >> ID;
	}
}

void File::PrintEnemies(List<Enemy*>& l)
{
	if (!output.is_open())
	{
		string n="output("+name+").txt";
		output.open(n);
		output << "KTS\tS\tFD\tKD\tLT" << endl; // for the first time output
	}
	l.begin();
	while (l.getSize())
	{
		Enemy* e = l.pop();
		AllFD += e->getfirstshootdelay(); // increase the first shot delay
		AllKD += e->killdelay(); // increase the kill delay
		Killed++;
		output << e->killed_time_step() << "\t" << e->getID() << "\t" << e->getfirstshootdelay() << "\t" << e->killdelay() << "\t" << e->lifetime() << endl;
	}
}

void File::TotalDamage(double T1,double T2,double T3,double T4)
{
	output<<endl<<endl;
	output<<"T1_Total_Damage\t  T2_Total_Damage\t  T3_Total_Damage\t  T4_Total_Damage"<<endl;
	output<<fixed<<setprecision(2)<<"\t"<<T1<<"\t\t"<<T2<<"\t\t\t"<<T3<<"\t\t\t"<<T4<<endl;
}

void File::UnPavedDis(int&R1,int&R2,int&R3,int&R4)
{
	output<<endl<<endl;
	output<<"R1_Unpaved_Dist\t  R2_Unpaved_Dist\t  R3_Unpaved_Dist\t  R4_Unpaved_Dist"<<endl;
	output<<"\t"<<R1<<"\t\t"<<R2<<"\t\t\t"<<R3<<"\t\t\t"<<R3<<endl;
}

void File::Win(bool win) // send true if win
{
	output << endl << endl;
	if (win)
	{
		output << "Game is WIN" << endl << endl;
		output << "Total Enemies\t=" << Total << endl << endl;
		output << "Average First_Shot Delay\t=" << (double)AllFD / Total << endl << endl;
		output << "Average Kill Delay\t=" << (double)AllKD / Total;
	}
	else
	{
		output << "Game is LOSS" << endl << endl;
		output << "Killed Enemies\t=" << Killed << endl << endl;
		output << "Alive Enemies\t=" << Total - Killed << endl << endl;
		output << "Average First_Shot Delay\t=" << (double)AllFD / Killed << endl << endl;
		output << "Average Kill Delay\t=" << (double)AllKD / Killed;
	}
	input.close();
	output.close();
}


void File::clear() {
	Killed = 0;
	Total = 0;
	AllFD = 0;
	AllKD = 0;
	input.close();
	output.close();
}
