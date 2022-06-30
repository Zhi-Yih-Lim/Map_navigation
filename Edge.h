#ifndef EDGE_H
#define EDGE_H

// Forward declration for the inclusion of the "Vertex.h" in "Edge.cpp" to avoid cicular dependencies
class Vertex;

// Header file for Edge object

class Edge{
	
	// Pointers to parent and child 
	Vertex *VParent, *VChild;
	
	// Weight of the current edge
	int Weight;

	public:
	// Default constructor
	Edge();
	// Overloaded constructor
	Edge(Vertex* P, Vertex* C, int weight);

	// Member functions that set the state of the edge object
	void SetWeight(int W);
	void SetParent(Vertex* VP);
	void SetChild(Vertex* VC);

	// Member functions that inquire the state of the edge
	int GetWeight();
	Vertex* GetParent();
	Vertex* GetChild();

};
#endif
