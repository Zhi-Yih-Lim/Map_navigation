#include "Maze.h"
#include <iostream>

int main (void){


	// Size of each cell and the grid
	int CSize = 50, GSize = 45;

	// Create a new player
	Player P1;

	char GTitle[] = "The Grid";
	Maze G(CSize,GSize);

	std::cout << "Finished Instantiating" << std::endl;
	
	Mat FGrid = G.PlotGrid();	
	std::tuple<int,int> begCoord = G.SetPeak(10);
	G.ColorGrid(FGrid);

	
	// Draw the player onto the grid
	G.DrawPlayer(FGrid,std::get<0>(begCoord),std::get<1>(begCoord),1,'b',P1);

	imshow(GTitle,FGrid);
	waitKey(0);

	// "Graphify" the cells into vertices and edges
	// Instantiate a tuple that will store two coordinate-tuples indicating 
	// the source and the target for the shortest-path search algorithm
	std::tuple<Vertex*,Vertex*> Temp = G.Graphify(P1);

	std::tuple<int,int> SourceCoord, TargetCoord;
	Vertex* SourceVertex = std::get<0>(Temp), *TargetVertex = std::get<1>(Temp);

	std::vector<std::tuple<int,int>> ShortestPath = G.FindShortestPath(SourceVertex, TargetVertex);
	
	// Mark the shortest path from the payer to the destination
	G.DrawPath(FGrid,ShortestPath,P1);

	imshow(GTitle,FGrid);
	waitKey(0);

	return(0);

}

