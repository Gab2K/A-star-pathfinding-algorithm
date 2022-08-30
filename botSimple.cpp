#include "bots.h"


void cBotSimple::ChooseNextGridPosition()
{
	//bot position
	int x = PositionX();
	int y = PositionY();

	if (gAStar.path.size() == 0)
	{
		if (gTarget.PositionX() > x)
		{
			SetNext((x + 1), (y), gLevel);
		}
		if (gTarget.PositionX() < x)
		{
			SetNext((x - 1), (y), gLevel);
		}
		if (gTarget.PositionY() > y)
		{
			SetNext((x), (y + 1), gLevel);
		}
		if (gTarget.PositionY() < y)
		{
			SetNext((x), (y - 1), gLevel);
		}
	}
	else
	{
		for (int i = gAStar.path.size() - 1; i >= 0; i--)
		{
			SetNext((gAStar.path.at(i).x), (gAStar.path.at(i).y), gLevel);

		}
	}
	}
	

	

