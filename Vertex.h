#ifndef VERTEX_H
#define VERTEX_H
#include "Cell.h"
#include "Edge.h"
#include <iostream>

// Header file for Vertex object

class Vertex{
	// Pointer to a Cell object
	Cell* CellRef;

	// Parent pointer that points to a another vertex
	Vertex* ParentPntr;

	// Shortest - path estimate from the source
	int ShortestPathWeight;

	// Each cell with the exception of the cells 
	// in the top and bottom columns along with the 
	// cells in the left and right rows will have 
	// 8 edges in total
	Edge *FN, *BN, *FNE, *BNE, *FE, *BE, *FSE, *BSE, *FS, *BS, *FSW, *BSW, *FW, *BW, *FNW, *BNW;


	public:
	//Constructors
	Vertex();

	// Member functions that set the state of the 
	// vertex
	void linkVertex2Cell(Cell* CPntr);
	void SetCellLinked();
	void SetVertexParent(Vertex* VParent);
	void SetShortestPathEstimate(int newEst);
	void SetEdge(char F, int Direction, Edge* E);

	// Member functions that inquire the state of the
	// vertex
	std::tuple<int,int> GetCoord();
	//Edge* GetEdge(int Dir);
	int GetSP();
	int GetCHeight();
	bool IfFullyLinked();
	void ShowParent();
	//void ShowEdges();
	void ShowSPEst();
	void ShowLinkCell();
	Vertex* GetParentPntr();






};
#endif
