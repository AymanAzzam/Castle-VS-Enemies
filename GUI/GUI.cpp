#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");

	pWind->DrawImage("images\\Covers\\start.jpg",0,0,1200,650);
	PlaySound("Sounds\\Guage Shotgun.wav",NULL,SND_FILENAME | SND_SYNC);
	PlaySound("Sounds\\Guage Shotgun.wav",NULL,SND_FILENAME | SND_SYNC);
	PlaySound("Sounds\\yes-hahahaa.wav",NULL,SND_FILENAME | SND_SYNC);

	ClearMenuBar();

	DrawMenu();

	ClearStatusBar();
	ClearBattleArea();
	DrawCastle();
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	pWind->DrawImage("images\\Covers\\end.jpg",0,0,1200,650);
	PlaySound("Sounds\\shotgun-mossberg.wav",NULL,SND_FILENAME | SND_SYNC);
	PlaySound("Sounds\\GunGuru.wav",NULL,SND_FILENAME | SND_SYNC);
	PrintMessage(100,"Bye",-470,100);
	PrintMessage(100,"Bye",-470,1000);
	PlaySound("Sounds\\bye-bye-1.wav",NULL,SND_FILENAME | SND_SYNC);

	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->FlushMouseQueue(); //This is necessary because if someone accidentally hits a click in mouse that event will stay in the buffer
	//until it is removed, which may that input would not be wanted by the user
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	pWind->FlushKeyQueue();  //This is necessary because if someone accidentally hits a key that event will stay in the buffer until it
	//is removed, which that input would not be wanted by the user
	pWind->WaitKeyPress(Key); // beacuse of clear the status bar when he start writing the name (whi i did this !! beacuse of BackSpace) 
	while(1)
	{
		ClearStatusBar();
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
		{
			ClearStatusBar();
			Label.resize(Label.size() -1 );
		}
		else
			Label += Key;
		
		PrintMessage(18,Label);
		pWind->WaitKeyPress(Key);
	}
}

void GUI::drawPavedTower(REGION region, int unpaved) const {
	int x, y, refX, refY;
	refX = WindWidth / 2;
	refY = YHalfBattleArea - 1;
	int hCastleWidth = floor(CastleWidth / 2.0 + 1);
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (region)
	{
	case A_REG:
		x = refX - hCastleWidth - (unpaved - 1) * (EnemyWidth + 1); //(Distance)
		y = MenuBarHeight; // YPos
		break;
	case B_REG:
		x = refX + hCastleWidth + (unpaved - 1) * (EnemyWidth + 1); //(Distance)
		y = MenuBarHeight; // YPos
		break;
	case C_REG:
		x = refX + hCastleWidth + (unpaved - 1) * (EnemyWidth + 1); //(Distance)
		y = WindHeight;
		break;
	case D_REG:
		x = refX - hCastleWidth - (unpaved - 1) * (EnemyWidth + 1);
		y = WindHeight;
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(PALEGOLDENROD);
	pWind->SetBrush(PALEGOLDENROD);
	pWind->DrawRectangle(x, y, refX, refY);
}

void GUI::drawPaved(Castle * castle) const
{
	for (int i = 0; i < 4; i++) {
		REGION region = static_cast<REGION>(i);
		drawPavedTower(region, castle->getUnPavedDistance(region));
	}
}

MenuItem GUI::getAction(bool clearQueue) {
	Point p;
	if (clearQueue) {
		GetPointClicked(p);
	}
	else {
		pWind->GetMouseClick(p.x, p.y);
		if (p.x == -1)
			return Battle_Area;
	}
	if (p.x > MENU_ITM_COUNT*MenuItemWidth || p.y > MenuBarHeight)
		return Battle_Area;
	return static_cast<MenuItem>(p.x / MenuItemWidth);
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(int font,string msg,int y,int x) const	//Prints a message on status bar
{
	//ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(BLACK);
	pWind->SetFont(font, BOLD , BY_NAME, "Arial");   //font 13 instead of 18
	pWind->DrawString(x, WindHeight + y - (int) (StatusBarHeight), msg); // You may need to change these coordinates later 
	                                                                      // to be able to write multi-line
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK);
	pWind->SetFont(13, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];

	MenuItemImages[interactive_mode] = "images\\MenuItems\\interactive.jpg";
	MenuItemImages[step_by_step_mode] = "images\\MenuItems\\step_by_step.jpg";
	MenuItemImages[silent_mode] = "images\\MenuItems\\silent.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//MenuItemImages[MENU_LOAD] = "images\\MenuItems\\Menu_Load.jpg";

	//
	//TODO: Prepare images for each menu item (an icon for each modes) and add it to the list
	//

	// You should add an icon for each mode of operation (silent, step by step, ...etc.)

	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	/*pWind->SetPen(GAINSBORO, 3);
	pWind->SetBrush(GAINSBORO);
	*/
	pWind->SetPen(GAINSBORO, 3);
	pWind->SetBrush(GAINSBORO);
	
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(AZURE, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearMenuBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0 , WindWidth, MenuBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle() const
{
	int L = CastleWidth / 2;

	// 1- Drawing the brown square of the castle
	pWind->SetPen(AZURE);
	pWind->SetBrush(AZURE);
	pWind->DrawArc(CastleStartX, CastleStartY, CastleEndX, CastleEndY,90,90);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(AZURE, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the castle)
	pWind->SetPen(BLACK);
	pWind->DrawLine(WindWidth/2, YHalfBattleArea - CastleWidth/2, WindWidth/2, YHalfBattleArea + CastleWidth/2);
	pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfBattleArea, WindWidth/2 + CastleWidth/2, YHalfBattleArea);

	// 4- Drawing the 4 white squares inside the castle (one for each tower)
	pWind->SetPen(BLACK);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(CastleStartX + L/3, CastleStartY + L/3, CastleStartX + 2*L/3, CastleStartY + 2*L/3);
	pWind->DrawRectangle(CastleStartX + L/3, CastleEndY - L/3, CastleStartX + 2*L/3, CastleEndY - 2*L/3);
	pWind->DrawRectangle(CastleEndX - 2*L/3, CastleStartY + L/3, CastleEndX - L/3, CastleStartY + 2*L/3);
	pWind->DrawRectangle(CastleEndX - 2*L/3, CastleEndY - L/3, CastleEndX - L/3, CastleEndY - 2*L/3);

	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(GAINSBORO);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + 0.44*L, CastleStartY + 5*L/12, "A");
	pWind->DrawString(CastleStartX + 0.44*L, YHalfBattleArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + 0.44*L, CastleStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + 0.44*L, YHalfBattleArea + 5*L/12, "C");

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	pWind->DrawLine(CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, MenuBarHeight,
		CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, WindHeight-StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, MenuBarHeight,
		CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, WindHeight-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy& E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) //const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		                        // else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region && !enemies[i]->iskilled())
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region && !enemies[i]->iskilled())
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			ClearStatusBar();
			PrintMessage(18,"Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}
//////////////////////////////////////////////////////////
void GUI::PrintCastleInfo(Queue<string>&q)
{
	int x = -300,y=0;
	string message;
	ClearStatusBar();

	while (!q.empty())
	{
		message = q.pop();
		if(message[0]=='A'||message[0]=='B'||message[0]=='C'||message[0]=='D')
		{
			y=0;
			x+=300;
			if(x!=0)
			{
				pWind->SetPen(BLACK);
				pWind->DrawLine(x-2,500,x-2,650);
			}
		}
		DrawString(2+x,500+y,message);
		y += 16;
	}
}