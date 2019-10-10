#include "Battle.h"

int main()
{

	Battle* pBattle = new Battle;
	bool haveAction = false;
	MenuItem action;
	bool exit = false;
	while (!exit) {
		if (!haveAction)
			action = pBattle->getAction();
		else {
			pBattle->clear();
		}
		try {
			while (action != MENU_EXIT)
			{
				pBattle->execute(action);
				action = pBattle->getAction();
			}
			exit = true;
		}
		catch (MenuItem item) {
			switch (item)
			{
			case MENU_EXIT:
				exit = true;
				break;
			default:
				action = item;
				haveAction = true;
				break;
			}
		}
	}
	delete pBattle;

}
