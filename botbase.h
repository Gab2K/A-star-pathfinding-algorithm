#pragma once
//======================================================================================
//Header for a bot base class. All bot classes should inherit from this, and define
//their own implementation of ChooseNextGridPosition
//======================================================================================

#include "dynamic.h"

class cBotBase: public cDynamic
{
public:
	virtual void Update(int ms)
	{
		cDynamic::Update(ms);
		if (!isMoving()) ChooseNextGridPosition();
	}
	//======================================================================================
	//ChooseNextGridPosition is a pure virtual function: there is no default implementation
	//and inheriting classes should provide their own version of this function.
	//======================================================================================
	virtual void ChooseNextGridPosition() = 0;
};