#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//======================================================================================

#include "botbase.h"
#include <vector>


class cBotSimple : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cBotSimple2 : public cBotBase
{
	virtual void ChooseNextGridPosition();
};


class cDijkstra
{
public:
	virtual void Build(cBotBase& bot);

	bool closed[GRIDWIDTH][GRIDHEIGHT]; //whether or not location is closed
	float cost[GRIDWIDTH][GRIDHEIGHT]; //cost value for each location
	int linkX[GRIDWIDTH][GRIDHEIGHT]; //link X coord for each location
	int linkY[GRIDWIDTH][GRIDHEIGHT]; //link Y coord for each location
	bool inPath[GRIDWIDTH][GRIDHEIGHT]; //whether or not a location is in the final path

	bool completed; // checks to see if the program is completed

	cDijkstra() // sets completed as false as default 
	{
		completed = false;
	}
	
};




class cAStar: public cDijkstra
{ 
public:
	virtual void Build(cBotBase& bot);

	//Path vector
	struct Path
	{
		int x;
		int y;
	};

	std::vector<Path> path;
	
};

class cAStar_euclidean : public cDijkstra
{
public:
	virtual void Build(cBotBase& bot);
};

class cAStar_diagonal : public cDijkstra
{
public:
	virtual void Build(cBotBase& bot);
};

extern cAStar gAStar;
extern cDijkstra gDijkstra;
extern cAStar_euclidean gAStar_euclidean;
extern cAStar_diagonal gAStar_diagonal;
