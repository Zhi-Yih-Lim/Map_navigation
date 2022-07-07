#ifndef Maze_H
#define Maze_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Cell.h"
#include "Player.h"
#include "Vertex.h"
#include <vector>
#include <math.h>
#include <time.h>
#include <queue>

using namespace cv;

class Maze{

	int CSize,GSize, thickness, lineType;	

	// Instantiate an array of edges that will be accessed for shortest path solving
	Edge** EdgeArr;

	// Allocate and array that will store vertex object instances to be used
	Vertex** VertexArr;
	
	// Instantiate a 2-dimensional array of pointers to Cell object instances
	Cell*** Grid;

	public:
	// Constructors for the Maze class
	Maze();
	~Maze();
	Maze(int Cell_s, int Grid_s);

	// Member functions 
	Mat PlotGrid();
	std::tuple<int,int> SetPeak(int NOPeaks);
	void ColorGrid(Mat G);
	void DrawPlayer(Mat G, int x, int y, int orient, char color,Player &P);
	void DrawPath(Mat G, std::vector<std::tuple<int,int>>Coord,Player &P);
	
	// Method to print out the edges
	void ShowEdges();


	// A function that converts the cells of the grid to vertices of a graph
	// with edges connecting the vertices. The edge will indicate the effort
	// required to traverse from one cell to another
	// This method accepts no arguments and returns two tuples, one indicating the 
	// source of the graph and the other indicating the target location. The method also returns a pointer to the source vertex. These 
	// values will be used to solve the shortest path.
	std::tuple<Vertex*, Vertex*> Graphify(Player P);

	// Find the shortest path from the source to the target
	// Function will return a vector of tuples
	std::vector<std::tuple<int,int>> FindShortestPath(Vertex* Source, Vertex* Target);
	

};//end class Maze
#endif
