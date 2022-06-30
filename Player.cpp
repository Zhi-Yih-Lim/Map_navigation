#include "Player.h"
#include "Cell.h"
#include <iostream>

Player::Player(){
	xC = yC = pathIdx =  0;
	orient = 1;
	destX = destY = -1;
}

std::tuple<int,int> Player::GetPos(){
	return std::make_tuple(xC,yC);
}

int Player::GetOrient(){
	return orient;
}

bool Player::onPeak(Cell*** arr){
	// Check to see if the current location
	// of the player is on a cell that is 
	// a peak
	if (arr[xC][yC]->isPeak()){
		return true;
	}
	else{
		return false;
	}
}

std::tuple<int,int> Player::NextPos(){
	pathIdx++;
	return (*Path2Dest)[pathIdx]; 
}

void Player::SetPos(std::tuple<int,int> Coord){
	xC = std::get<0>(Coord);
	yC = std::get<1>(Coord);
}

void Player::SetOrient(int dir){
	orient = dir;
}

void Player::SetDest(std::tuple<int,int> Dest){
	destX = std::get<0>(Dest);
	destY = std::get<1>(Dest);
}

void Player::SetPath(std::vector<std::tuple<int,int>> &P2Dest){
	Path2Dest = &P2Dest;
}
	
