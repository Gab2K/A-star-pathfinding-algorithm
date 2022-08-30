#include "bots.h"



int i = 0;

void cBotSimple2::ChooseNextGridPosition()
{
	//If path vector is not empty
	if (gAStar.path.size() > 0)
	{
		//Sets i to an index of bot's location
		i = gAStar.path.size();
	}

	//If index is not 0 then move the bot
	if (i != 0)
	{
		i--;
		int x = gAStar.path.at(i).x - PositionX();
		int y = gAStar.path.at(i).y - PositionY();
		
		SetNext((PositionX() + x), PositionY() + y, gLevel);

		//After each move erase the location from the vector
		gAStar.path.erase(gAStar.path.begin() + i);
	}

	//Clear the vector after player and bot coordinates are the same
	if (PositionX() == gTarget.PositionX() && PositionY() == gTarget.PositionY())
	{
		gAStar.path.clear();
	}
}