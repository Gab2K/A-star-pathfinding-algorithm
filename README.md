# Pathfinding algorithm A STAR

A-star-pathfinding-algorithm

This project is an A* pathfinding algorithm which is widely used in games to approximate the shortest path from the Bot to the player avoiding any obstacles like walls.

The program uses 3 different heuristics methods: manhattan distance, diagonal distance and euclidean distance.

The program loads a selected map, with 2 objects. The red circle represents the player and can be moved using the cursor keys. The green object is a bot. By pressing p, r or s the bot will generate a path to the player and then follow it. The red blocks represent a path from the bot to the player whilst the blue path represents the blocks that were scanned by the algorithm to determine the path.
How to use


Press p, r or s to create a path that the bot will follow to catch the player. The following keys represent the specific heuristic methods:

P = Manhattan

R = Euclidean

S = Diagonal

Map can be changed in main.cpp on line 69

## How to run
To launch run PathFinderCpp.sln in Visual Studio\
Change debug from x64 to x86
![image](https://user-images.githubusercontent.com/60928508/187550348-d74ba5d5-8bf4-4e77-9441-8efb60e41a4b.png)

