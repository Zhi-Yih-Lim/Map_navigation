#include "Edge.h"
#include "Vertex.h"
#include <iostream>

Edge::Edge(){
	Weight = 2000000000;
	VParent = VChild = nullptr;
}

Edge::Edge(Vertex* P, Vertex* C, int weight){
	VParent = P;
	VChild = C;
	Weight = weight;
}

void Edge::SetWeight(int W){

	Weight = W;

}

void Edge::SetParent(Vertex* VP){
	VParent = VP;
}

void Edge::SetChild(Vertex* VC){
	VChild = VC;
}

int Edge::GetWeight(){

	return Weight;

}

Vertex* Edge::GetParent(){
	return VParent;
}

Vertex* Edge::GetChild(){
	return VChild;
}


 
