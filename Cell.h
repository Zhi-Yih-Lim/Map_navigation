#ifndef CELL_H
#include <tuple>
#define CELL_H

// Forward declaration for vertex class 
class Vertex;

// This is a header file for Cell.h and will store only the class 
// declaration along with its members

class Cell{
	// A variable that keep tracks if the current cell contains player 1 or 2
	bool contain_p1, contain_p2, peak;
	// X and Y Coordinates of the current cell in the maze
	int xC, yC;
	// The RGB value for the current cell
	int r,g,b;
	// Keeps track of the existence of the borders for each cell
	bool top,btm,left,right;
	// Variable to keep track of whether this cell has been fully edge-linked
	bool EdgeLinked;
	// The elevation of each cell
	int elev;
	// Boolean variable to keep track of whether a vertex has been assigned to the current cell
	bool VertexAssigned;
	// Variable to keep track of the vertex object the current cell is linked to
	Vertex* LinkedVertex;

	public:
	// Constructor for the current class
	Cell();
	//~Cell();
	Cell(int x,int y,int elev);
	
	// Member functions that enquires the state of the cell
	bool CheckOccupied();
	bool isPeak();
	std::tuple<int,int> GetCoord();
	int GetElev();
	int GetBVal();
	int GetGVal();
	int GetRVal();
	bool CheckLinked();
	bool CheckVertexAssigned();
	bool CheckTop();
	bool CheckBtm();
	bool CheckLeft();
	bool CheckRight();
	Vertex* GetVertex();

	// Member functions that sets the parameters of the current cell
	void SetCoord(int x, int y);
	void SetElev(int h);
	void SetColor(int b, int g, int r);
	void SetEdgeLinked();
	void SetVertex(Vertex* V);
	void OpenTop();
	void OpenBtm();
	void OpenLeft();
	void OpenRight();
	void toggleP1();
	void toggleP2();
	void toggleEmpty();
	void togglePeak();

};
#endif
