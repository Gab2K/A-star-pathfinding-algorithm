#include "bots.h"
#include <vector>
#include <algorithm>

void cDijkstra :: Build(cBotBase& bot)
{
	//Initializing all the grids
	for (size_t i = 0; i < 40; i++)
	{
		for (size_t j = 0; j < 40; j++)
		{
			closed[i][j] = false;
			cost[i][j] = 10000000.0f;
			linkX[i][i] = -1;
			linkY[i][j] = -1;
			inPath[i][j] = false;
		}
	}


	std::vector <float> lowestCost;
	std::vector <int> lowestCostX;
	std::vector <int> lowestCostY;

	lowestCostX.push_back(bot.PositionX()); //Adding x coordinate
	lowestCostY.push_back(bot.PositionY()); //Adding y coordinate

	cost[bot.PositionX()][bot.PositionY()] = 0; //Bots cost is set to 0
	lowestCost.push_back(cost[bot.PositionX()][bot.PositionY()]); //Adding cost to the vector



	
	while (!closed[gTarget.PositionX()][gTarget.PositionY()] && lowestCost.size() != 0) //While player's node has not been closed or the cost vector is not empty
	{

		//Find element with lowest value and get its index
		int minIndex = std::min_element(lowestCost.begin(), lowestCost.end()) - lowestCost.begin();


		//Save coordinates of the lowest value into temporary integers
		int tempX = lowestCostX.at(minIndex);
		int tempY = lowestCostY.at(minIndex);

		//Close it
		closed[tempX][tempY] = true;

		
		//Remove closed grid from vector
		lowestCost.erase(lowestCost.begin() + minIndex);
		lowestCostX.erase(lowestCostX.begin() + minIndex);
		lowestCostY.erase(lowestCostY.begin() + minIndex);
		
		
		//Calculate cost of neighbours if they're not blocked or closed

		//For each neighbour it's cost and X and Y coordinates are added to a vector
		//then the neighbour is linked back to the location that was just closed

		//up

		//if the block is not closed and is not closed and the new cost won't be higher than it already is
		if (closed[tempX][tempY +1] == false && gLevel.isValid(tempX, (tempY + 1)))
		{
			//if the block's new value is better than it's exisiting value or it's currently at 0
			if (cost[tempX][tempY + 1] > cost[tempX][tempY] + 1 or cost[tempX][tempY + 1] == 10000000)
			{
				cost[tempX][tempY + 1] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX][tempY + 1]);
				lowestCostX.push_back(tempX);
				lowestCostY.push_back(tempY + 1);
				linkX[tempX][tempY + 1] = tempX;
				linkY[tempX][tempY + 1] = tempY;
			}
		}
			
		
		//down
		if (closed[tempX][tempY -1] == false && gLevel.isValid(tempX, (tempY -1)))
		{
			if (cost[tempX][tempY - 1] > cost[tempX][tempY] + 1 or cost[tempX][tempY - 1] == 10000000)
			{
				cost[tempX][tempY - 1] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX][tempY - 1]);
				lowestCostX.push_back(tempX);
				lowestCostY.push_back(tempY - 1);
				linkX[tempX][tempY - 1] = tempX;
				linkY[tempX][tempY - 1] = tempY;
			}
			
		}
			

		// left
		if (closed[tempX - 1][tempY] == false && gLevel.isValid((tempX - 1), tempY))
		{
			if (closed[tempX - 1][tempY] > cost [tempX][tempY]+1 or cost[tempX -1][tempY] == 10000000)
			{
				cost[tempX - 1][tempY] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX - 1][tempY]);
				lowestCostX.push_back(tempX - 1);
				lowestCostY.push_back(tempY);
				linkX[tempX - 1][tempY] = tempX;
				linkY[tempX - 1][tempY] = tempY;

			}
			
		}
	

	//	//right
		if (closed[tempX + 1][tempY] == false && gLevel.isValid((tempX + 1), tempY))
		{
			if (closed[tempX + 1][tempY] > cost[tempX][tempY] + 1 or cost[tempX + 1][tempY] == 10000000)
			{
				cost[tempX + 1][tempY] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX + 1][tempY]);
				lowestCostX.push_back(tempX + 1);
				lowestCostY.push_back(tempY);
				linkX[tempX + 1][tempY] = tempX;
				linkY[tempX + 1][tempY] = tempY;
			}
			
		}
		

	//top left
		if (closed[tempX -1][tempY + 1] == false && gLevel.isValid((tempX -1), (tempY + 1)))
		{
			if (closed[tempX - 1][tempY + 1] > cost[tempX][tempY] + 1.4f or cost[tempX - 1][tempY + 1] == 10000000)
			{
				cost[tempX - 1][tempY + 1] = cost[tempX][tempY] + 1.4f; 
				lowestCost.push_back(cost[tempX - 1][tempY + 1]);
				lowestCostX.push_back(tempX - 1);
				lowestCostY.push_back(tempY + 1);
				linkX[tempX - 1][tempY + 1] = tempX;
				linkY[tempX - 1][tempY + 1] = tempY;
			}
		
		}


	//top right
		if (closed[tempX + 1][tempY + 1] == false && gLevel.isValid((tempX + 1), (tempY + 1)))
		{
			if (closed[tempX + 1][tempY + 1] > cost[tempX][tempY] + 1.4f or cost[tempX + 1][tempY + 1] == 10000000)
			{
				cost[tempX + 1][tempY + 1] = cost[tempX][tempY] + 1.4f; 
				lowestCost.push_back(cost[tempX + 1][tempY + 1]);
				lowestCostX.push_back(tempX + 1);
				lowestCostY.push_back(tempY + 1);
				linkX[tempX + 1][tempY + 1] = tempX;
				linkY[tempX + 1][tempY + 1] = tempY;
			}
			
		}


	//bottom left
		if (closed[tempX - 1][tempY - 1] == false && gLevel.isValid((tempX - 1), (tempY - 1)))
		{
			if (closed[tempX - 1][tempY - 1] > cost[tempX][tempY] + 1.4f or cost[tempX - 1][tempY - 1] == 10000000)
			{
				cost[tempX - 1][tempY - 1] = cost[tempX][tempY] + 1.4f; 
				lowestCost.push_back(cost[tempX - 1][tempY - 1]);
				lowestCostX.push_back(tempX - 1);
				lowestCostY.push_back(tempY - 1);
				linkX[tempX - 1][tempY - 1] = tempX;
				linkY[tempX - 1][tempY - 1] = tempY;
			}

		}


	//bottom right
		if (closed[tempX + 1][tempY - 1] == false && gLevel.isValid((tempX + 1), (tempY - 1)))
		{
			if (closed[tempX + 1][tempY - 1] > cost[tempX][tempY] + 1.4f or cost[tempX + 1][tempY - 1] == 10000000)
			{
				cost[tempX + 1][tempY - 1] = cost[tempX][tempY] + 1.4f; 
				lowestCost.push_back(cost[tempX + 1][tempY - 1]);
				lowestCostX.push_back(tempX + 1);
				lowestCostY.push_back(tempY - 1);
				linkX[tempX + 1][tempY - 1] = tempX;
				linkY[tempX + 1][tempY - 1] = tempY;
			}
			
		}
		

		
	}


	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY()))
		{
			done = true;
		}
			
	}
	completed = true;

	
	
}

cDijkstra gDijkstra;