#include "Cell.h"
#include "Vertex.h"


Cell::Cell(){
	xC = yC = -1;
	elev = 1;
	contain_p1 = contain_p2 = peak = false;
	r = g = b = 255;
	top = btm = left = right = true;
	EdgeLinked = false;
	VertexAssigned = false;
}

Cell::Cell(int x, int y, int elev){
	xC = yC = x;
	yC = y;
	this->elev = elev;
	contain_p1 = contain_p2 = peak = false;
	r = g = b = 255;
	top = btm = left = right = true;
	EdgeLinked = false;
	VertexAssigned = false;
}

bool Cell::CheckOccupied(){
	if (contain_p1||contain_p2){
		return true;
	}
	else{
		return false;
	}
}

bool Cell::isPeak(){
	if(peak){
		return true;
	}
	else{
		return false;
	}
}

std::tuple<int,int> Cell::GetCoord(){

	return std::make_tuple(xC,yC);

}	

int Cell::GetElev(){
	return elev;
}

int Cell::GetBVal(){
	return b;
}

int Cell::GetGVal(){
	return g;
}

int Cell::GetRVal(){
	return r;
}

bool Cell::CheckLinked(){
	return EdgeLinked;
}

bool Cell::CheckVertexAssigned(){
	return VertexAssigned;
}

bool Cell::CheckTop(){
	if (top){
		return true;
	}
	else{
		return false;
	}
}

bool Cell::CheckBtm(){
	if (btm){
		return true;
	}
	else{
		return false;
	}
}

bool Cell::CheckLeft(){
	if (left){
		return true;
	}
	else{
		return false;
	}
}

bool Cell::CheckRight(){
	if (right){
		return true;
	}
	else{
		return false;
	}
}

Vertex* Cell::GetVertex(){
	return LinkedVertex;
}

void Cell::SetCoord(int x, int y){
	xC = x;
	yC = y;
}

void Cell::SetElev(int h){
	elev = h;
}

void Cell::SetColor(int b, int g, int r){
	this->r = r;
	this->g = g;
	this->b = b;
}

void Cell::SetEdgeLinked(){
	EdgeLinked = true;
}

void Cell::SetVertex(Vertex* V){
	LinkedVertex = V;
	VertexAssigned = true;
}

void Cell::OpenTop(){
	top = false;
}

void Cell::OpenBtm(){
	btm = false;
}

void Cell::OpenLeft(){
	left = false;
}

void Cell::OpenRight(){
	right = false;
}

void Cell::toggleP1(){
	(contain_p1)?contain_p1=false:contain_p1=true;
}

void Cell::toggleP2(){
	(contain_p2)?contain_p2=false:contain_p2=true;
}

void Cell::toggleEmpty(){
	contain_p1 = contain_p2 = false;
}

void Cell::togglePeak(){
	(peak)?peak=false:peak=true;
}
