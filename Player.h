#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Cell.h"

// Header file for Player object
// Header file will contain the class definitions
// constructors and member functions

class Player{
	// The location of the current player
	int xC, yC;

	// Variable to record the index of of the path 
	// to destination vector
	int pathIdx = -1;

	// The orientation of the current player
	// There will be a total of eight orientations
	// possible.
	int orient;

	// Destination of the current player
	int destX, destY;

	// Path to destination for the current player
	// stored as tuples in a vector
	// "Path2Dest" is a pointer to a vector
	// of coordinate tuples.
	std::vector<std::tuple<int,int>>* Path2Dest;	

	public:
	// Constructors
	Player();

	// Member functions that enquire the state of the player
	std::tuple<int, int> GetPos();
	int GetOrient();
	bool onPeak(Cell*** arr);
	std::tuple<int,int> NextPos();

	// Member functions that set the state of the player
	void SetPos(std::tuple<int, int> Coord);
	void SetOrient(int dir);
	void SetDest(std::tuple<int, int> Dest);
	void SetPath(std::vector<std::tuple<int,int>> &P2Dest);

	// Destructor for the class
	~Player();



};
#endif
