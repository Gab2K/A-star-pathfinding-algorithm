#include "bots.h"
#include <vector>
#include <algorithm>

void cAStar_diagonal::Build(cBotBase& bot)
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
	std::vector <float> lowestCostX;
	std::vector <int> lowestCostY;


	lowestCostX.push_back(bot.PositionX()); //Adding x coordinate
	lowestCostY.push_back(bot.PositionY()); //Adding y coordinate

	int x = bot.PositionX();
	int y = bot.PositionY();

	cost[bot.PositionX()][bot.PositionY()] = 0; //Bots cost is set to 0

	//Initial heuristic is calculated for the bot's position

	float heuristic = fabs(x - gTarget.PositionX()) + fabs(y - gTarget.PositionY()) - (0.6) * std::min(fabs(x - gTarget.PositionX()), fabs(y - gTarget.PositionY()));

	lowestCost.push_back(cost[bot.PositionX()][bot.PositionY()] + heuristic); //Adding cost to the vector


	while (!closed[gTarget.PositionX()][gTarget.PositionY()] && lowestCost.size() != 0) //While player's node has not been closed or the cost vector is not empty
	{

		//Find element with lowest value and get its index
		int minIndex = std::min_element(lowestCost.begin(), lowestCost.end()) - lowestCost.begin();


		//Save coordinates of the lowest value into temporary integers
		int tempX = lowestCostX.at(minIndex);
		int tempY = lowestCostY.at(minIndex);

		// resetting heuristic
		heuristic = 0;


		//Close it
		closed[tempX][tempY] = true;


		//Remove closed grid from vector and cost
		lowestCost.erase(lowestCost.begin() + minIndex);
		lowestCostX.erase(lowestCostX.begin() + minIndex);
		lowestCostY.erase(lowestCostY.begin() + minIndex);


		//Calculate cost of neighbours if they're not blocked or closed

		//For each neighbour it's cost and heuristic cost; X and Y coordinates are added to a vector
		//then the neighbour is linked back to the location that was just closed

		//up

		//if the block is not closed and is not closed and the new cost won't be higher than it already is
		if (closed[tempX][tempY + 1] == false && gLevel.isValid(tempX, (tempY + 1)))
		{
			//if the block's new value is better than it's exisiting value or it's currently at 10000000
			if (cost[tempX][tempY + 1] > cost[tempX][tempY] + 1 or cost[tempX][tempY + 1] == 10000000)
			{
				heuristic = fabs(tempX - gTarget.PositionX()) + fabs((tempY +1) - gTarget.PositionY()) - (0.6) * std::min(fabs(tempX - gTarget.PositionX()), fabs((tempY + 1) - gTarget.PositionY()));
				cost[tempX][tempY + 1] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX][tempY + 1] + heuristic);
				lowestCostX.push_back(tempX);
				lowestCostY.push_back((tempY + 1));
				linkX[tempX][tempY + 1] = tempX;
				linkY[tempX][tempY + 1] = tempY;
			}
		}


		//down
		if (closed[tempX][tempY - 1] == false && gLevel.isValid(tempX, (tempY - 1)))
		{
			if (cost[tempX][tempY - 1] > cost[tempX][tempY] + 1 or cost[tempX][tempY - 1] == 10000000)
			{
				heuristic = fabs(tempX - gTarget.PositionX()) + fabs((tempY - 1) - gTarget.PositionY()) - (0.6) * std::min(fabs(tempX - gTarget.PositionX()), fabs((tempY - 1) - gTarget.PositionY()));
				cost[tempX][tempY - 1] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX][tempY - 1] + heuristic);
				lowestCostX.push_back(tempX);
				lowestCostY.push_back(tempY - 1);
				linkX[tempX][tempY - 1] = tempX;
				linkY[tempX][tempY - 1] = tempY;
			}

		}


		// left
		if (closed[tempX - 1][tempY] == false && gLevel.isValid((tempX - 1), tempY))
		{
			if (closed[tempX - 1][tempY] > cost[tempX][tempY] + 1 or cost[tempX - 1][tempY] == 10000000)
			{
				heuristic = fabs((tempX - 1) - gTarget.PositionX()) + fabs(tempY - gTarget.PositionY()) - (0.6) * std::min(fabs((tempX - 1) - gTarget.PositionX()), fabs(tempY - gTarget.PositionY()));
				cost[tempX - 1][tempY] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX - 1][tempY] + heuristic);
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
				heuristic = fabs((tempX + 1) - gTarget.PositionX()) + fabs(tempY - gTarget.PositionY()) - (0.6) * std::min(fabs((tempX + 1) - gTarget.PositionX()), fabs(tempY - gTarget.PositionY()));
				cost[tempX + 1][tempY] = cost[tempX][tempY] + 1;
				lowestCost.push_back(cost[tempX + 1][tempY] + heuristic);
				lowestCostX.push_back(tempX + 1);
				lowestCostY.push_back(tempY);
				linkX[tempX + 1][tempY] = tempX;
				linkY[tempX + 1][tempY] = tempY;
			}

		}


		//top left
		if (closed[tempX - 1][tempY + 1] == false && gLevel.isValid((tempX - 1), (tempY + 1)))
		{
			if (closed[tempX - 1][tempY + 1] > cost[tempX][tempY] + 1.4f or cost[tempX - 1][tempY + 1] == 10000000)
			{
				heuristic = fabs((tempX - 1) - gTarget.PositionX()) + fabs((tempY + 1) - gTarget.PositionY()) - (0.6) * std::min(fabs((tempX - 1) - gTarget.PositionX()), fabs((tempY + 1) - gTarget.PositionY()));
				cost[tempX - 1][tempY + 1] = cost[tempX][tempY] + 1.4f;
				lowestCost.push_back(cost[tempX - 1][tempY + 1] + heuristic);
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
				heuristic = fabs((tempX + 1) - gTarget.PositionX()) + fabs((tempY + 1) - gTarget.PositionY()) - (0.6) * std::min(fabs((tempX + 1) - gTarget.PositionX()), fabs((tempY + 1) - gTarget.PositionY()));
				cost[tempX + 1][tempY + 1] = cost[tempX][tempY] + 1.4f;
				lowestCost.push_back(cost[tempX + 1][tempY + 1] + heuristic);
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
				heuristic = fabs((tempX - 1) - gTarget.PositionX()) + fabs((tempY - 1) - gTarget.PositionY()) - (0.6) * std::min(fabs((tempX - 1) - gTarget.PositionX()), fabs((tempY - 1) - gTarget.PositionY()));
				cost[tempX - 1][tempY - 1] = cost[tempX][tempY] + 1.4f;
				lowestCost.push_back(cost[tempX - 1][tempY - 1] + heuristic);
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
				heuristic = fabs((tempX + 1) - gTarget.PositionX()) + fabs((tempY - 1) - gTarget.PositionY()) - (0.6) * std::min(fabs((tempX + 1) - gTarget.PositionX()), fabs((tempY - 1) - gTarget.PositionY()));
				cost[tempX + 1][tempY - 1] = cost[tempX][tempY] + 1.4f;
				lowestCost.push_back(cost[tempX + 1][tempY - 1] + heuristic);
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


	//Clear the vector before using
	gAStar.path.clear();
	//Add players grid location first
	gAStar.path.push_back({ gTarget.PositionX(), gTarget.PositionY() });

	//Find the path from bot to player adding it to the vector
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		gAStar.path.push_back({ nextClosedX, nextClosedY });
		if ((gAStar.path.back().x == bot.PositionX()) && (gAStar.path.back().y == bot.PositionY()))
		{
			done = true;
		}

	}

	completed = true;
}

cAStar_diagonal gAStar_diagonal;