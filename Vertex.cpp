#include "Vertex.h"

Vertex::Vertex(){

	// Set all of the pointers to intially be NULL
	CellRef = nullptr; 
	ParentPntr = nullptr; 
	FN = BN = FNE = BNE = FE = BE = FSE = BSE = FS = BS = FSW = BSW = FW = BW = FNW = BNW = nullptr;

	// Set the shortest path weight to be infinity
	ShortestPathWeight = 2000000000;
	
}

std::tuple<int,int> Vertex::GetCoord(){

	std::tuple<int,int> CellCoord  = CellRef->GetCoord();
	return std::make_tuple(std::get<0>(CellCoord),std::get<1>(CellCoord));

}

/*
Edge* Vertex::GetEdge(int Dir){

	switch(Dir){
		case 0:
			return eParent;
			break;
		case 1:
			return eN;
			break;
		case 2:
			return eNE;
			break;
		case 3:
			return eE;
			break;
		case 4:
			return eSE;
			break;
		case 5:
			return eS;
			break;
		case 6:
			return eSW;
			break;
		case 7:
			return eW;
			break;
		case 8:
			return eNW;
			break;
		default:
			return nullptr;
			break;
	}// end switch
	

}
*/

int Vertex::GetSP(){
	return ShortestPathWeight;
}

int Vertex::GetCHeight(){
	return CellRef->GetElev();
}

bool Vertex::IfFullyLinked(){
	return CellRef->CheckLinked();
}

void Vertex::ShowParent(){

	// Obtain the current coordinates of the cell object pointed to by the current vertex
	std::tuple<int,int> Coord = ParentPntr -> GetCoord();
	int row = std::get<0>(Coord), col = std::get<1>(Coord);

	std::cout << "The parent of this node is at location " << row << ',' << col << std::endl;

}


/*
void Vertex::ShowEdges(){

	if (ParentPntr != NULL){
		// Get the coordinates of the parent vertex and the weight of the parent edge
		//this -> ShowParent();
		int PEWeight = eParent -> GetWeight();

		std::cout << "This vertex has a parent edge whose weight is [" << PEWeight << ']' << std::endl;

	}

	if (eN != NULL){	
		
		std::cout << "This vertex has an edge in the north" << std::endl;


		int NeWeight = eN -> GetWeight();

		std::cout << " The weight of the edge in the north direction is " << NeWeight << std::endl;

	}


	if (eNE != NULL){	

		std::cout << "This vertex has an edge in the north-east" << std::endl;


		int NEeWeight = eNE -> GetWeight();

		std::cout << " The weight of the edge in the north-east direction is " << NEeWeight << std::endl;

	}


	if (eE != NULL){	
		std::cout << "This vertex has an edge in the east" << std::endl;


		int EeWeight = eE -> GetWeight();

		std::cout << " The weight of the edge in the east direction is " << EeWeight << std::endl;
	}

	if (eSE != NULL){	
		std::cout << "This vertex has an edge in the south-east" << std::endl;


		int SEeWeight = eSE -> GetWeight();

		std::cout << " The weight of the edge in the south-east direction is " << SEeWeight << std::endl;
	}

	if (eS != NULL){	
		std::cout << "This vertex has an edge in the south" << std::endl;


		int SeWeight = eS -> GetWeight();

		std::cout << " The weight of the edge in the south direction is " << SeWeight << std::endl;
	}

	if (eSW != NULL){	
		std::cout << "This vertex has an edge in the south-west" << std::endl;


		int SWeWeight = eSW -> GetWeight();

		std::cout << " The weight of the edge in the south-west direction is " << SWeWeight << std::endl;
	}

	if (eW != NULL){	
		std::cout << "This vertex has an edge in the west" << std::endl;


		int WeWeight = eW -> GetWeight();

		std::cout << " The weight of the edge in the west direction is " << WeWeight << std::endl;
	}

	if (eNW != NULL){	
		std::cout << "This vertex has an edge in the north-west" << std::endl;

		int NWeWeight = eNW -> GetWeight();

		std::cout << " The weight of the edge in the north-west direction is " << NWeWeight << std::endl;
	}

	std::cout << std::endl << std::endl;

}
*/

void Vertex::ShowSPEst(){

	(this -> GetSP() < 2000000000) ? std::cout << "The shorest path weight estimate currently is " << this -> GetSP() << std::endl : std::cout << "The shortest path weight is INF" << std::endl;

}

void Vertex::ShowLinkCell(){
	// Obtain the coodinates of the cell linked to by this vertex
	std::tuple<int,int> Coord = CellRef -> GetCoord();

	if (CellRef != NULL){
		std::cout << "The vertex is linked to a cell at coordinate (" << std::get<0>(Coord) << ',' << std::get<1>(Coord) << ')' <<  std::endl;
	}
	else{

		std::cout << "The current vertex is not linked to any cell" << std::endl;

	}
}


void Vertex::linkVertex2Cell(Cell* CPntr){

	// Simply point "CellRef" to CPtnr
	CellRef = CPntr;

	//this -> ShowLinkCell();

}

void Vertex::SetCellLinked(){
	CellRef -> SetEdgeLinked();
}

void Vertex::SetVertexParent(Vertex* VParent){

	// Simply point "ParentPntr" to VParent
	ParentPntr = VParent;

	//this -> ShowParent();

}

void Vertex::SetShortestPathEstimate(int newEst){
	
	ShortestPathWeight = newEst;

	this -> ShowSPEst();

}

void Vertex::SetEdge(char F, int Direction, Edge* E){

	switch(F){

		case 'O':

			switch(Direction){
				
				case 1:
					FN = E;
					break;

				case 2:
					FNE = E;
					break;

				case 3:
					FE = E;
					break;

				case 4:
					FSE = E;
					break;

				case 5:
					FS = E;
					break;

				case 6:
					FSW = E;
					break;

				case 7:
					FW = E;
					break;

				case 8:
					FNW = E;
					break;
			}

			break;
		
		case 'I':

			switch(Direction){
				
				case 1:
					BE = E;
					break;

				case 2:
					BNE = E;
					break;

				case 3:
					BE = E;
					break;

				case 4:
					BSE = E;
					break;

				case 5:
					BS = E;
					break;

				case 6:
					BSW = E;
					break;

				case 7:
					BW = E;
					break;

				case 8:
					BNW = E;
					break;
			}

			break;

	}//end swtich

	//this -> ShowEdges();
}

Vertex* Vertex::GetParentPntr(){

	return ParentPntr;

}
