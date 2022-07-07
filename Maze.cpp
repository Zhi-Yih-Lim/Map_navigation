#include "Maze.h"
#include <iostream>
#include <stack>
#include <cmath>

Maze::Maze(){
	CSize = 50;
	GSize = 30;
	thickness = 1;
	lineType = LINE_8;

	// Set the size of the edge and vertex arrays
	int NOEdges = (GSize*GSize*8) - (2*(GSize-1)*6) - 8, NOVertex = GSize*GSize;
	EdgeArr = new Edge*[NOEdges];
	VertexArr = new Vertex*[NOVertex];


	// Create an array for the edges
	for (int e=0; e<(GSize*GSize*8); e++){
		EdgeArr[e] = new Edge;
	}

	// Create an array for the vertices
	for (int v=0; v<(GSize*GSize); v++){
		VertexArr[v] = new Vertex;
	}

	// Create a new array
	Grid = new Cell** [GSize];
	for(int r=0; r<GSize; r++){
		Grid[r] = new Cell* [GSize];
	}// end for

	// Populate "Grid" with pointers to 
	// "Cell" object instances
	for(int row=0; row<GSize; row++){
		for (int col=0; col<GSize; col++){
			Grid[col][row] = new Cell();
			Grid[col][row] -> SetCoord(col,row);
		}
	}
}

Maze::Maze(int Cell_s, int Grid_s){
	CSize = Cell_s;
	GSize = Grid_s;
	thickness = 1;
	lineType = LINE_8;

	// Set the size of the edge and vertex arrays
	int NOEdges = (GSize*GSize*8) - (2*(GSize-1)*6) - 8, NOVertex = GSize*GSize;
	EdgeArr = new Edge*[NOEdges];
	VertexArr = new Vertex*[NOVertex];

	// Create an array for the edges
	for (int e=0; e<(GSize*GSize*8); e++){
		EdgeArr[e] = new Edge;
	}

	// Create an array for the vertices
	for (int v=0; v<(GSize*GSize); v++){
		VertexArr[v] = new Vertex;
	}

	// Create a new array
	Grid = new Cell** [GSize];
	for(int r=0; r<GSize; r++){
		Grid[r] = new Cell* [GSize];
	}// end for

	// Populate "Grid" with pointers to 
	// "Cell" object instances
	for(int row=0; row<GSize; row++){
		for (int col=0; col<GSize; col++){
			Grid[col][row] = new Cell();
			Grid[col][row] -> SetCoord(col,row);
		}
	}
}

Maze:~Maze(){
	// Delete the edges and the vertices
	delete[] EdgeArr;
	delete[] VertexArr;

	// Delete the each "Cell" instance manually
	for (int col=0; col<GSize; col++){
		for (int row=0; row<GSize; row++){
			delete Grid[col][row];
		}
		// When all row elements have been deleted, delete the entire column
		delete[] Grid[col];
	}

	delete[] Grid;
}

Mat Maze::PlotGrid(){
	// Calculate the total number of cells on the grid
	// There will be altogether [thickness * (GSize + 1)] 
	// extra lines in the column and row to accomodate the
	// borders of the cells
	int ttlWidth = (CSize * GSize) + ((GSize + 1)*thickness);

	// With the size of the grid available, instantiate the 
	// grid
	Mat FGrid = Mat(ttlWidth,ttlWidth,CV_8UC3,Scalar(160,160,160));

	// Plot the cell boundaries in the grid
	for(int r=0;r<GSize;r++){
		for(int c=0;c<GSize;c++){
			// Each cell will definitely have a right and a bottom 
			// boundary. 
			// Cells in the first row will have and an additional top 
			// boundary
			if(r==0){
				// Need coodinates for the top line
				int TLX = (c*(CSize + thickness)), TLY = (r*(CSize + thickness)),TRX = ((c+1)*(CSize + thickness)), TRY = (r*(CSize + thickness));

				// Instantiate tuple for the starting and ending coordinates of the top line
				std::tuple <int,int> TopLS = std::make_tuple(TLX,TLY), TopLE = std::make_tuple(TRX,TRY);
				// Plot the top line 
				line(FGrid,Point(std::get<0>(TopLS),std::get<1>(TopLS)),Point(std::get<0>(TopLE),std::get<1>(TopLE)),Scalar(0,0,0),thickness,lineType);

			}//end if r == 0

			// Cells in the first column will need to have a left boundary
			if (c==0){
				// Need coordinates for the left line	
				int BLX = (c*(CSize + thickness)), BLY = ((r+1)*(CSize + thickness));
				int TLX = (c*(CSize + thickness)), TLY = (r*(CSize + thickness));
				
				// Instantiate tuple for the staring and ending coordinates for the left boundary
				std::tuple <int,int> LeftLS = std::make_tuple(BLX,BLY), LeftLE = std::make_tuple(TLX,TLY);

				// Plot the left line
				line(FGrid,Point(std::get<0>(LeftLS),std::get<1>(LeftLS)),Point(std::get<0>(LeftLE),std::get<1>(LeftLE)),Scalar(0,0,0),thickness,lineType);		
				
			}// end if c == 0

			// For all other cases, plot the right and bottom lines only	
			int TRX = ((c+1)*(CSize + thickness)), TRY = (r*(CSize + thickness));	
			int BRX = ((c+1)*(CSize + thickness)), BRY = ((r+1)*(CSize + thickness));	
			int BLX = (c*(CSize + thickness)), BLY = ((r+1)*(CSize + thickness));

			// Check first to see if the right boundary needs to be plotted
			if (Grid[c][r]->CheckRight()){

				// Instantiate tuple for the starting and ending coordinates for the right line
				std::tuple <int,int> RightLS = std::make_tuple(TRX,TRY), RightLE = std::make_tuple(BRX,BRY);

				// Plot the right line 	
				line(FGrid,Point(std::get<0>(RightLS),std::get<1>(RightLS)),Point(std::get<0>(RightLE),std::get<1>(RightLE)),Scalar(0,0,0),thickness,lineType);	

			}// end if Grid[c][r]->CheckRight()

			
			// Check first to see if the bottom boundary needs to be plotted
			if (Grid[c][r]->CheckBtm()){

				// Instantiate tuple for the starting and ending coordinates for the bottom line
				std::tuple <int,int> BtmLS = std::make_tuple(BLX,BLY), BtmLE = std::make_tuple(BRX,BRY);

				// Plot the bottom line
				line(FGrid,Point(std::get<0>(BtmLS),std::get<1>(BtmLS)),Point(std::get<0>(BtmLE),std::get<1>(BtmLE)),Scalar(0,0,0),thickness,lineType);

			}// end if Grid[c][r]->CheckBtm()

		}// end for c

	}// end for r

	return FGrid;

}// end "Mat Maze"


std::tuple<int,int> Maze:: SetPeak (int NOPeaks){

	bool pFound;
	int pX, pY, CElev, pHeight, minP = 11;
	std::tuple<int,int> Coord;
	
	// Seeding the random generator
	srand(time(NULL));

	// Populate the grid with peaks
	for(int p=NOPeaks; p>0; p--){

		std::cout << "Peak " << p << std::endl;
		// Defaults to the current peak has not yet been found
		pFound = false;	


		// The X and Y coordinates of the current peak will be randomly generated
		// if the current set of coordinates already contains a peak, re-generate
		// the coordinates
		while(!pFound){
			
			// Randomly generate an X and Y coordinate for a peak
			pX = rand()%GSize;
			pY = rand()%GSize;	

			// The first peak will have an elevation of 10
			// The elevation for the remaining peaks will 
			// be randomly generated
			if (p==NOPeaks){
				pHeight = 10;
			}
			else{
				// Randomize the pHeight value to be any value between
				// 2 and 9
				pHeight = rand()%8 + 2;

			}// end else

			// See if the generated coordinates is already a peak
			if((!Grid[pX][pY]->isPeak())&&(pHeight > Grid[pX][pY]->GetElev())){
				//Set the current cell's peak attribute to be true
				Grid[pX][pY]->togglePeak();

				// Exit the while loop
				pFound = true;

			}// end if 
		
		}// end while	
	
		//Randomize the x and y constants for the paraboloid
		float xC = (-1.0*(rand()%100 + 1)/1000), yC = (-1.0*(rand()%100 + 1)/1000);

		//Set the elevation of every single pixel with the current equation
		for (int c=0; c < GSize; c++){
			for (int r=0; r < GSize; r++){

				// Compute the elevation for the current cell
				CElev = (xC*pow((c-pX),2)) + (yC*pow((r-pY),2)) + pHeight;
				
				// If the calculated elevation value is larger than the current elevation value
				// of the current cell
				if (CElev>Grid[c][r]->GetElev()){
					
					// Set set the "CElev" attribute of the current cell
					Grid[c][r]->SetElev(CElev);

				}//end if
				
				// If we are currently computing the elevation for each cell using the parameters for 
				// the last peak
				if (p==1){
					
					// If "CElev" for the current cell is less than "minP", save its location
					if (Grid[c][r]->GetElev()<minP){

						minP = Grid[c][r]->GetElev();
						std::get<0>(Coord) = c;
						std::get<1>(Coord) = r;

					}// end if Grid[c][r]->GetElev

				}// end if p==1

			}// end for int r

		}// end for int c

	}//end for int p

	// Return a starting location for the player.
	return Coord;
	
}// end "SetPeak"

void Maze::ColorGrid(Mat G){
	
	int elev;

	// Color each grid individually
	for (int r=0; r<GSize; r++){
		for (int c=0; c<GSize; c++){
		
			// Get the elevation value of the current cell
			elev = Grid[c][r]->GetElev();
	
			// Compute the coloring area of the current cell	
			int BegCol = (c*(CSize + thickness)) + thickness, EndCol = ((c+1)*(CSize + thickness)) - thickness; 
			int BegRow = (r*(CSize + thickness)) + thickness, EndRow = ((r+1)*(CSize + thickness)) - thickness;

			// Based on the elevation value of the current cell, color all of the pixels
			switch(elev){
				case 1:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(255,0,127);	
						}
					}
					break;
				case 2:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(255,0,0);
						}	
					}
					break;

				case 3:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(255,128,0);
						}	
					}
					break;
				
				case 4:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(255,255,0);
						}	
					}
					break;
				
				case 5:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(128,255,0);
						}	
					}
					break;
				
				case 6:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(0,255,0);
						}	
					}
					break;
				
				case 7:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(0,255,128);
						}	
					}
					break;
				
				case 8:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(0,255,255);
						}	
					}
					break;
				
				case 9:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(0,128,255);
						}	
					}
					break;
				
				case 10:
					for (int x=BegCol; x <= EndCol; x++){
						for (int y = BegRow; y <= EndRow; y++){
							G.at<Vec3b>(y,x) = Vec3b(0,0,255);
						}	
					}
					break;
			}// end switch
		}// end for int c
	}// end for int r

}// end ColorGrid

void Maze::DrawPlayer(Mat G, int x, int y, int orient, char color, Player &P){

	//Set the coordinates of the player
	std::tuple<int,int> currentPos(x,y);
	P.SetPos(currentPos);

	// Calculate the midpoint for the current cell 
	// with the provided x and y coordinates	
	int TLX = (x*(CSize + thickness)), TLY = (y*(CSize + thickness));	
	int TRX = ((x+1)*(CSize + thickness)), TRY = (y*(CSize + thickness));	
	int BRX = ((x+1)*(CSize + thickness)), BRY = ((y+1)*(CSize + thickness));	
	int BLX = (x*(CSize + thickness)), BLY = ((y+1)*(CSize + thickness));
	
	int midX = (BLX + BRX)/2, midY = (BLY + TLY)/2;
	
	// Calculate the distance from the midpoint of the current cell to one of the boundaries
	int arrFrontLen = (BRX-1) - midX;

	// The back of the triangle will extend "backwards" from the midpoint at a length that is 
	// half of that of the front length
	int arrBackLen = arrFrontLen/2;

	// Based on the orientation, set the vertices of the arrow accordingly
	// First, instantiate an array of "Point" objects three rows
	Point Player_points[1][3];

	// Varaibels that stores the coordinates of the end of the back line of the arrow 
	// used to compute the coordinates of the arrow when in 45 degrees in any direction
	int backX, backY;

	switch(orient){
		case 1:
			// The player points north
			Player_points[0][0] = Point(midX,midY - arrFrontLen);
			Player_points[0][1] = Point(midX + arrBackLen, midY + arrBackLen);
			Player_points[0][2] = Point(midX - arrBackLen, midY + arrBackLen);
			
			break;
		case 2:
			// The player points north east
			Player_points[0][0] = Point(midX+(int)(arrFrontLen*cos(0.785398)),midY-(int)(arrFrontLen*sin(0.785398)));		

			// Calculate the coordinates of the back part of the arrow
			backX = midX-(int)(arrBackLen*cos(0.785398));
			backY = midY+(int)(arrBackLen*sin(0.785398));

			// Calculate the coordinates for the top left end of the back coordinates
			Player_points[0][1] = Point(backX+(int)(arrBackLen*cos(0.785398)),backY+(int)(arrBackLen*sin(0.785398)));
			Player_points[0][2] = Point(backX-(int)(arrBackLen*cos(0.785398)),backY-(int)(arrBackLen*sin(0.785398)));
			
			break;
		case 3:
			// The player points east
			Player_points[0][0] = Point(midX+arrFrontLen, midY);
			Player_points[0][1] = Point(midX-arrBackLen, midY+arrBackLen);
			Player_points[0][2] = Point(midX-arrBackLen, midY-arrBackLen);

			break;
		case 4:
			// The player points South east
			Player_points[0][0] = Point(midX+(int)(arrFrontLen*cos(0.785398)),midY+(int)(arrFrontLen*sin(0.785398)));
			
			// Calculate the coordintaes of the back part of the arrow
			backX = midX-(int)(arrBackLen*cos(0.785398));
			backY = midY-(int)(arrBackLen*sin(0.785398));

			// Calculate the coordinates for the top left end of the back coordinates
			Player_points[0][1] = Point(backX+(int)(arrBackLen*cos(0.785398)),backY-(int)(arrBackLen*sin(0.785398)));
			Player_points[0][2] = Point(backX-(int)(arrBackLen*cos(0.785398)),backY+(int)(arrBackLen*sin(0.785398)));

			break;
		case 5:
			// The player points South	
			Player_points[0][0] = Point(midX,midY + arrFrontLen);
			Player_points[0][1] = Point(midX - arrBackLen, midY - arrBackLen);
			Player_points[0][2] = Point(midX + arrBackLen, midY - arrBackLen);
			
			break;

		case 6:
			// The player points south west
			Player_points[0][0] = Point(midX-(int)(arrFrontLen*cos(0.785398)),midY+(int)(arrFrontLen*sin(0.785398)));
			
			// Calculate the coordintaes of the back part of the arrow
			backX = midX+(int)(arrBackLen*cos(0.785398));
			backY = midY-(int)(arrBackLen*sin(0.785398));

			// Calculate the coordinates for the top right end of the back coordinates
			Player_points[0][1] = Point(backX+(int)(arrBackLen*cos(0.785398)),backY+(int)(arrBackLen*sin(0.785398)));
			Player_points[0][2] = Point(backX-(int)(arrBackLen*cos(0.785398)),backY-(int)(arrBackLen*sin(0.785398)));

			break;
		case 7:	
			// The player points West	
			Player_points[0][0] = Point(midX-arrFrontLen,midY);
			Player_points[0][1] = Point(midX + arrBackLen, midY - arrBackLen);
			Player_points[0][2] = Point(midX + arrBackLen, midY + arrBackLen);
			
			break;
		case 8:

			// The player points North West
			Player_points[0][0] = Point(midX-(int)(arrFrontLen*cos(0.785398)),midY-(int)(arrFrontLen*sin(0.785398)));		

			// Calculate the coordinates of the back part of the arrow
			backX = midX+(int)(arrBackLen*cos(0.785398));
			backY = midY+(int)(arrBackLen*sin(0.785398));

			// Calculate the coordinates for the top left end of the back coordinates
			Player_points[0][1] = Point(backX+(int)(arrBackLen*cos(0.785398)),backY-(int)(arrBackLen*sin(0.785398)));
			Player_points[0][2] = Point(backX-(int)(arrBackLen*cos(0.785398)),backY+(int)(arrBackLen*sin(0.785398)));
			
			break;
	}// end switch
	
	// Use "fillPloy" to draw the player on the grid
	int npt[] = {3};
	const Point* ppt[1] = {Player_points[0]};

	fillPoly(G,ppt,npt,1,Scalar(0,0,0),LINE_8);

}// end DrawPlayer

void Maze::DrawPath(Mat G, std::vector<std::tuple<int,int>>Coord, Player &P){
	// Traverse through the vector of tuples
	int vecSize = Coord.size();
	int col, row;
	uchar blue, green, red;
	
	for (int i=0; i<vecSize; i++){
			
		// Obtain the x and y coordinates from the 
		// input vector of tuples
		col = std::get<0>(Coord.at(i));
		row = std::get<1>(Coord.at(i));

		// Compute the coloring area of the current cell	
		int BegCol = (col*(CSize + thickness)) + thickness, EndCol = ((col+1)*(CSize + thickness)) - thickness; 
		int BegRow = (row*(CSize + thickness)) + thickness, EndRow = ((row+1)*(CSize + thickness)) - thickness;

		/*

		// Obtain the color of the current cell
		Vec3b intensity = G.at<Vec3b>(BegRow,BegCol);
		blue = intensity.val[0];
		green = intensity.val[1];
		red = intensity.val[2];

		// Based on the current bgr value, increase them to their desired value
		if ((blue == 128)||(blue==127)){
			blue = 178;
		}
		else if(blue == 0){
			blue = 102;
		}

		if ((red == 128)||(red==127)){
			red = 178;
		}
		else if(red == 0){
			red = 102;
		}

		if ((green == 128)||(green==127)){
			green = 178;
		}
		else if(green == 0){
			green = 102;
		}


		*/

		// Color the cell gray
		for (int SCol=BegCol; SCol <= EndCol; SCol++){
			for (int SRow = BegRow; SRow <= EndRow; SRow++){
				// Color the cells grey
				G.at<Vec3b>(SRow,SCol) = Vec3b(160,160,160);	
				// Color the cells the whiter color of their current color
				//G.at<Vec3b>(y,x) = Vec3b(blue,green,red);	
			}// end for y
		}// end for x


		// If we are currently on the first tuple, this is where the player is, color the grid
		// and draw the player in the direction that the next shortest path cell will be in
		if (i == 0){
			// Get the coordinates of the second cell
			int col2 = std::get<0>(Coord.at(1));
			int row2 = std::get<1>(Coord.at(1));
			int dir = 0;

			// Determine the direction of the following cell
			// If the following cell is in the same row
			if (row == row2){
				// If the following cell is to the right of the current cell
				if (col2 > col){
					// Set direction for east
					dir = 3;
				}
				else{
					// Set direction for west
					dir = 7;
				}	

			}// end if the rows are the same
	
			// If the columns are the same
			else if (col == col2){
				// If the following row is to the top of teh current cell
				if (row2 < row){
					// Set direction for north
					dir = 1;
				}
				else{
					//Set direction for south
					dir = 5;
				}
			}// end if the columns are the same

			// If neither the columns nor the rows are the same
			else{
				// If the row of the next cell is to the top or bottom of the current cell
				if (row2 < row){
					// If the column is to the left of the current column
					if(col2 < col){
						//Set direction for northwest
						dir = 8;
					}
					else{
						// Set direction for northeast
						dir = 2;
					}
				
				}//end if the row for the second cell is less than the row of the first cell
				
				// If the row of the second cell is at the bottom of the current cell
				else{
					if(col2 < col){
						//Set direction for southwest
						dir = 6;
					}
					else{
						//Set direction for southeast
						dir = 4;
					}
				}//end else 


			}// end else for neither the columns nor the rows are similar


			// Draw the player in the intended direction
			this -> DrawPlayer(G, col, row, dir, 'b', P);

		}
		// If we are currently on the last tuple, this is the target. Color the grid and mark
		// the target with an "X"
		else if(i == vecSize-1){

			// Calculate the mid-row where addition needs to be flipped into subtractions
			int midRow = (EndRow+BegRow)/2, midCol = (EndCol+BegCol)/2;

			// Mark and 'X' on the cell in red
			for (int XCol=BegCol; XCol <= EndCol; XCol++){
				for (int XRow = BegRow; XRow <= EndRow; XRow++){
					if (XCol == midCol){
						G.at<Vec3b>(XRow,XCol) = Vec3b(0,0,0);
					}
					if (XRow == midRow){
						G.at<Vec3b>(XRow,XCol) = Vec3b(0,0,0);
					}
					if ((XRow - BegRow) == (XCol - BegCol)){
						// Color the cells red
						G.at<Vec3b>(XRow,XCol) = Vec3b(0,0,0);
					}
					if (XRow == (EndRow - (XCol-BegCol))){
						G.at<Vec3b>(XRow,XCol) = Vec3b(0,0,0);	
					}
									
				}// end for y
			}// end for x
	

		}// end else if the current tuple is the last tuple in the vector
		
	}// end for int i=0


}// end DrawPath



// Function will return a pointer to the source node and the coordinates of the start and target cells
std::tuple<Vertex*, Vertex*> Maze::Graphify(Player P){

	// Instantiate an array of edges to be returned for shortest path finding 
	// First, calculate the number of edges of the graph
	int EdgeCount = 0;
	int VertexCount = 0;

	// Instantiate a queue called Frontier
	std::queue<Vertex*> Frontier;

	// Instantiate the vertex pointers to be used later
	Vertex *Source,*Front,*Target,*North,*NorthEast,*East,*SouthEast,*South,*SouthWest,*West,*NorthWest;

	// Instantiate the Edge pointers to be used later
	Edge *OutE, *InE;

	// Link the source vertex to the source cell
	std::tuple<int,int> FrontCoord, PlayerCoord = P.GetPos();
	int SCol = std::get<0>(PlayerCoord), SRow = std::get<1>(PlayerCoord);

	// Return the pointer of the first vertex
	Source = VertexArr[VertexCount];
	Source->linkVertex2Cell(Grid[SCol][SRow]);
	Grid[SCol][SRow]->SetVertex(Source);
	Frontier.push(Source);

	// Increment the vertex count
	VertexCount++;

	// Variable to keep track of the total number of cells visited
	int CellsVisited = 0;

	// A function that returns the weight of an edge
	auto EdgeFunc = [](Vertex* From, Vertex* To, char dir){

		int HeightDiff,DiagDist,DiagHeight;

		// Calculate the height difference fron travelling to the next 
		// vertex from the current vertex
		HeightDiff = (To->GetCHeight() - From->GetCHeight())*3;
		
		switch(dir){
		
			case('s'):

				if (HeightDiff == 0){
					return (int) (To->GetCHeight())*10000;
				}
				else if(HeightDiff > 0){
					DiagHeight = sqrt(pow(To->GetCHeight(),2) + pow(HeightDiff,2))*10000;	
					return (int) DiagHeight+((To->GetCHeight())*10000);
				}				
				else{
					return (int) ((To->GetCHeight())*10000)/2;
				}
				break;

			case('d'):
				
				if (HeightDiff == 0){
					return (int) (To->GetCHeight()*2)*10000;
				}
				else if(HeightDiff > 0){
					DiagHeight = sqrt(pow(To->GetCHeight()*2,2) + pow(HeightDiff,2))*10000;
					return  DiagHeight + (int)((To->GetCHeight()*2)*10000);
				}				
				else{
					return (int) ((To->GetCHeight()*2)*10000)/2;
				}
				break;

			default:
				return 20000*2;


		}//end switch

	
	}; //end lambda function for calculating edge weights 

	// A function that links edges between the front vertex and a vertex in the South
	auto LinkSouth = [&](){

		// First, check if the cell in the south direction of the cell pointed to by the front vertex is already fully linked
		if (!Grid[SCol][SRow+1]->CheckLinked()){

			// Check if the cell has already been assigned a vertex
			if (!Grid[SCol][SRow+1]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				South = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol][SRow+1]->SetVertex(South);

				// Link the vertex to the current cell
				South->linkVertex2Cell(Grid[SCol][SRow+1]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				South = Grid[SCol][SRow+1]->GetVertex(); 

			}
			
			
			// Obtain the height values of the parent and calculate the edge weights for the outgoing and incoming edges
			int WOut = EdgeFunc(Front, South, 's');
			int WIn = EdgeFunc(South,Front,'s');
		
			// Create an out-going edge and an in-coming edge
			// Get new edge objects from the E array
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(South);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(South);
			InE -> SetChild(Front);
			EdgeCount++;

			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 5, OutE);
			South->SetEdge('I', 1, OutE);
			South->SetEdge('O', 1, InE);
			Front->SetEdge('I', 5, InE);
		
			std::cout<< "Adding South" << std::endl;
			
			// Add the child vertex to the frontier
			Frontier.push(South);
		}

	};// end lambda function for linking the front vertex to a vertex in the south

	// A function that links edges between the front vertex and a vertex in the North
	auto LinkNorth = [&](){

		// First, check if the cell in the south direction of the cell pointed to by the front vertex is already fully linked
		if (!Grid[SCol][SRow-1]->CheckLinked()){

			// Check if the cell has already been assigned a vertex
			if (!Grid[SCol][SRow-1]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				North = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol][SRow-1]->SetVertex(North);

				// Link the vertex to the current cell
				North->linkVertex2Cell(Grid[SCol][SRow-1]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				North = Grid[SCol][SRow-1]->GetVertex(); 

			}
			
			
			// Obtain the height values of the parent and calculate the edge weights for the outgoing and incoming edges
			int WOut = EdgeFunc(Front, North, 's');
			int WIn = EdgeFunc(North, Front,'s');
		
			// Create an out-going edge and an in-coming edge
			// Get new edge objects from the E array
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(North);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(North);
			InE -> SetChild(Front);
			EdgeCount++;

			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 1, OutE);
			North->SetEdge('I', 5, OutE);
			North->SetEdge('O', 5, InE);
			Front->SetEdge('I', 1, InE);
		
			std::cout<< "Adding North" << std::endl;
			
			// Add the child vertex to the frontier
			Frontier.push(North);
		}

	};// end lambda function for linking the front vertex to a vertex in the north

	// A function that links edges between the front vertex and a vertex in the East
	auto LinkEast = [&](){

		if (!Grid[SCol+1][SRow]->CheckLinked()){
			
			if (!Grid[SCol+1][SRow]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				East = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol+1][SRow]->SetVertex(East);

				// Link the vertex to the current cell
				East->linkVertex2Cell(Grid[SCol+1][SRow]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				East = Grid[SCol+1][SRow]->GetVertex(); 

			}

			// Obtain the height values of the parent and calculate the edge weights for the outgoing and incoming edges
			int WOut = EdgeFunc(Front, East, 's');
			int WIn = EdgeFunc(East, Front,'s');


			// Extract new edges from the 'E' array and populate them
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(East);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(East);
			InE -> SetChild(Front);
			EdgeCount++;
		
			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 3, OutE);
			East->SetEdge('I', 7, OutE);
			East->SetEdge('O', 7, InE);
			Front->SetEdge('I', 3, InE);

			std::cout<< "Adding East" << std::endl;

			// Add the child vertex to the frontier
			Frontier.push(East);

		}

	};// end lambda function for linking the front vertex to a vertex in the east

	// A function that links edges between the front vertex and a vertex in the west
	auto LinkWest = [&](){

		if (!Grid[SCol-1][SRow]->CheckLinked()){

			if (!Grid[SCol-1][SRow]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				West = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol-1][SRow]->SetVertex(West);

				// Link the vertex to the current cell
				West->linkVertex2Cell(Grid[SCol-1][SRow]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				West = Grid[SCol-1][SRow]->GetVertex(); 

			}

			// Obtain the height values of the parent and calculate the edge weights for the outgoing and incoming edges
			int WOut = EdgeFunc(Front, West, 's');
			int WIn = EdgeFunc(West, Front,'s');


			// Extract new edges from the 'E' array and populate them
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(West);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(West);
			InE -> SetChild(Front);
			EdgeCount++;
		
			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 7, OutE);
			West->SetEdge('I', 3, OutE);
			West->SetEdge('O', 3, InE);
			Front->SetEdge('I', 7, InE);


			// Add the child vertex to the frontier
			Frontier.push(West);
		}

	};// end lambda function for linking the front vertex to a vertex in the west

	// A function that links edges between the front vertex and a vertex in the north east
	auto LinkNorthEast = [&](){
		
		if (!Grid[SCol+1][SRow-1]->CheckLinked()){
						
			if (!Grid[SCol+1][SRow-1]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				NorthEast = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol+1][SRow-1]->SetVertex(NorthEast);

				// Link the vertex to the current cell
				NorthEast->linkVertex2Cell(Grid[SCol+1][SRow-1]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				NorthEast = Grid[SCol+1][SRow-1]->GetVertex(); 

			}

			// Obtain the height values of the parent and child vertex to calculate the weight
			int WOut = EdgeFunc(Front, NorthEast, 'd');
			int WIn = EdgeFunc(NorthEast, Front,'d');


			// Extract new edges from the 'E' array and populate them
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(NorthEast);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(NorthEast);
			InE -> SetChild(Front);
			EdgeCount++;					

			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 2, OutE);
			NorthEast->SetEdge('I', 6, OutE);
			NorthEast->SetEdge('O', 6, InE);
			Front->SetEdge('I', 2, InE);

			std::cout<< "Adding North East" << std::endl;

			// Add the child vertex to the frontier
			Frontier.push(NorthEast);
		}

	};// end lambda function for linking the front vertex to a vertex in the northeast

	// A function that links edges between the front vertex and a vertex in the northwest
	auto LinkNorthWest = [&](){
		
		if (!Grid[SCol-1][SRow-1]->CheckLinked()){

			if (!Grid[SCol-1][SRow-1]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				NorthWest = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol-1][SRow-1]->SetVertex(NorthWest);

				// Link the vertex to the current cell
				NorthWest->linkVertex2Cell(Grid[SCol-1][SRow-1]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				NorthWest = Grid[SCol-1][SRow-1]->GetVertex(); 

			}

			// Obtain the height values of the parent and child vertex to calculate the weight
			int WOut = EdgeFunc(Front, NorthWest, 'd');
			int WIn = EdgeFunc(NorthWest, Front,'d');


			// Extract new edges from the 'E' array and populate them
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(NorthWest);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(NorthWest);
			InE -> SetChild(Front);
			EdgeCount++;

		
			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 8, OutE);
			NorthWest->SetEdge('I', 4, OutE);
			NorthWest->SetEdge('O', 4, InE);
			Front->SetEdge('I', 8, InE);

			std::cout<< "Adding North West" << std::endl;

			// Add the child vertex to the frontier
			Frontier.push(NorthWest);

		}

	};// end lambda function for linking the front vertex to a vertex in the northwest

	// A function that links edges between the front vertex and a vertex in the southeast
	auto LinkSouthEast = [&](){

		if (!Grid[SCol+1][SRow+1]->CheckLinked()){
						
			if (!Grid[SCol+1][SRow+1]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				SouthEast = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol+1][SRow+1]->SetVertex(SouthEast);

				// Link the vertex to the current cell
				SouthEast->linkVertex2Cell(Grid[SCol+1][SRow+1]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				SouthEast = Grid[SCol+1][SRow+1]->GetVertex(); 

			}

			// Obtain the height values of the parent and child vertex to calculate the weight
			int WOut = EdgeFunc(Front, SouthEast, 'd');
			int WIn = EdgeFunc(SouthEast, Front,'d');

			// Extract new edges from the 'E' array and populate them
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(SouthEast);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(SouthEast);
			InE -> SetChild(Front);
			EdgeCount++;
		
			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 4, OutE);
			SouthEast->SetEdge('I', 8, OutE);
			SouthEast->SetEdge('O', 8, InE);
			Front->SetEdge('I', 4, InE);

			std::cout<< "Adding South East" << std::endl;

			// Add the child vertex to the frontier
			Frontier.push(SouthEast);
		}

	};// end lambda function for linking the front vertex to a vertex in the southeast

	// A function that links edges between the front vertex and a vertex in the southwest
	auto LinkSouthWest = [&](){

		if (!Grid[SCol-1][SRow+1]->CheckLinked()){

			if (!Grid[SCol-1][SRow+1]->CheckVertexAssigned()){

				// Get a new vertex from the 'V' input array
				SouthWest = VertexArr[VertexCount];
		
				// Link the current cell to the current vertex
				Grid[SCol-1][SRow+1]->SetVertex(SouthWest);

				// Link the vertex to the current cell
				SouthWest->linkVertex2Cell(Grid[SCol-1][SRow+1]);

				VertexCount++;
			}

			else{

				// If the cell in the specified direction already
				// has a vertex assigned to it, obtain the pointer
				// to that vertex
				SouthWest = Grid[SCol-1][SRow+1]->GetVertex(); 

			}

			// Obtain the height values of the parent and child vertex to calculate the weight
			int WOut = EdgeFunc(Front, SouthWest, 'd');
			int WIn = EdgeFunc(SouthWest, Front,'d');


			// Extract new edges from the 'E' array and populate them
			OutE = EdgeArr[EdgeCount];
			OutE -> SetWeight(WOut);
			OutE -> SetParent(Front);
			OutE -> SetChild(SouthWest);
			EdgeCount++;
			InE = EdgeArr[EdgeCount];
			InE -> SetWeight(WIn);
			InE -> SetParent(SouthWest);
			InE -> SetChild(Front);
			EdgeCount++;

		
			// Assign the edge to the respective locations of the parent and child vertices
			Front->SetEdge('O', 6, OutE);
			SouthWest->SetEdge('I', 2, OutE);
			SouthWest->SetEdge('O', 2, InE);
			Front->SetEdge('I', 6, InE);

			std::cout<< "Adding South West" << std::endl;

			// Add the child vertex to the frontier
			Frontier.push(SouthWest);

		}

	};// end lambda function for linking the front vertex to a vertex in the southwest
	
	// While the frontier is not empty, pop and process the nodes from the Frontier
	while (Frontier.size() > 0){

		// Process the first element in the frontier
		Front = Frontier.front();	

		// Get the height value of the current vertex
		if (Front->GetCHeight() == 10){
			Target = Frontier.front();
		} 	
	

		// Get the coordinates of the current front
		FrontCoord = Front->GetCoord();
		SCol = std::get<0>(FrontCoord); 
		SRow = std::get<1>(FrontCoord);

		// Check to see if the front vertex has already been fully linked
		if (!Front->IfFullyLinked()){

			// Increment the total number of cells visited
			CellsVisited++;

			std::cout << "Currently processing row : " << SRow << " col : " << SCol << std::endl;

			// Add the cells that are around the cell pointed to by the "Front" vertex
			// If the player is in the first row
			if (SRow == 0){

				//SOUTHINOUT
				LinkSouth();
				

			}// end if player is in the first row

			// If the player is in the last row
			else if(SRow == GSize-1){

				//NORTHINOUT
				LinkNorth();	

			}// end else if player is in the last row

			// If the player is not in the first or last row, we will need to look up and down
			else{

				LinkSouth();
				LinkNorth();	

			}//end else for if the player is not in the first nor the last row

			// If the player is in the first column
			if (SCol == 0){

				// If we are in the first column and we are in the first row
				if (SRow == 0){

					// We can look to the south-east
					//SOUTHEASTINOUT
					LinkSouthEast();

				}

				// If we are in the first column and we are in the last row
				else if(SRow == GSize-1){

					// We can only look to the north-east
					//NORTHEASTINOUT
					LinkNorthEast();

				}

				// If we are in the first column and we are not in the first or last row
				else{

					// We can add the north-east and south-east cells
					LinkNorthEast();
					LinkSouthEast();

				}
			

				// If we are in the first column, we can surely look to the east
				// EASTINOUT
				LinkEast();

			}// end if the player is in the first column

			// If the player is in the last column
			else if(SCol == GSize-1){

				// If we are in the last column and first row
				if (SRow == 0){

					// Check to see if the cell in the south-west has been fully linked
					//SOUTHWESTINOUT
					LinkSouthWest();

				}

				// If we are in the last column and last row
				else if(SRow == GSize - 1){

					// Check to see if the cell in the north-west has been fully linked
					//NORTHWESTINOUT
					LinkNorthWest();

				}

				// If we are in the last column and neither in the first not last row
				else{

					// We can look at both the south and north west directions
					LinkSouthWest();
					LinkNorthWest();

				} // end else for if we are in the last column but neither in the first nor last row.

				// If we are in the last column, we can surely look west
				//WESTINOUT
				LinkWest();

			}// end if the player is in the last column

			// If the player is not in the first nor the last column
			else{

				// If we are currently in the first row
				if(SRow == 0){

					// We can look south-east and south-west
					LinkSouthEast();
					LinkSouthWest();

				}

				// If we are in the last row
				else if(SRow == GSize - 1){
				
					// We can look in the north-east and north-west direction
					LinkNorthEast();
					LinkNorthWest();

				}

				// If we are not in the first nor last column and we are not in the first nor last row
				else{

					// We can look in the north-east, south-east, south-west and north-west directions
					LinkNorthEast();
					LinkNorthWest();
					LinkSouthEast();
					LinkSouthWest();

				}


				// If the player is not in the first nor the last column, we can look at the east and west
				LinkEast();
				LinkWest();

			}// end else if the player is not in the first nor the last column

			// Set the current cell to be already fully linked so that we do not have to process the cell again
			Front->SetCellLinked();

		}// end if the current vertex is not fully linked
		

		// After the finishing setting the front vertex, pop it from frontier
		Frontier.pop();

	}//end while frontier is not empty

	
	return std::make_tuple(Source,Target);


}// end Graphify

void Maze::ShowEdges(){
	
	for (int j=0; j < ((GSize*GSize*8) - (2*(GSize-1)*6) - 8) ; j++){
		
		std::tuple<int,int> ParentCoord = EdgeArr[j] -> GetParent() -> GetCoord(), ChildCoord = EdgeArr[j] -> GetChild() -> GetCoord();
		std::cout << "The coordinate of the parent of this edge is row :" << std::get<0>(ParentCoord) << ", col :" << std::get<1>(ParentCoord) << std::endl;
		std::cout << "The coordinate of the child of this edge is row :" << std::get<0>(ChildCoord) << ", col :" << std::get<1>(ChildCoord) << std::endl;
		std::cout << "The current edge's weight is " << EdgeArr[j] -> GetWeight() << std::endl << std::endl;
	}

}// end ShowEdges

std::vector<std::tuple<int,int>> Maze::FindShortestPath(Vertex* Source, Vertex* Target){

	// First, set the source vertex's weight to be zero
	Source -> SetShortestPathEstimate(0);	

	// Instantiate a vector to be returned
	std::vector<std::tuple<int,int>> RtrnVec;

	// Instantiate a FILO stack to store the pointers to the vertices of the shortest path
	std::stack<Vertex*> ReversedShortestPath;

	// Calculate the total number of vertices and the total number of edges
	int TtlV = GSize*GSize, TtlE = (GSize*GSize*8) - (2*(GSize-1)*6) - 8; 

	// Variables to store the pointers to the parent and child vertices of each edge
	Vertex *ParentV, *ChildV;

	// Variable to store the calculation of the new weight estimate
	int newEstimate;

	for(int v=0; v<TtlV; v++){

		for (int e=0; e<TtlE; e++){

			// Obtain the parent and child vertices of this edge
			ParentV = EdgeArr[e] -> GetParent();
			ChildV = EdgeArr[e] -> GetChild();
			
			// Relax the shortest path estimate of the child
			if (ParentV -> GetSP() != 2000000000){

				// Calculate the child vertex estimate
				newEstimate = ParentV->GetSP() + EdgeArr[e] -> GetWeight();	

				// If the new estimate is less than the current shortest path
				// estimate of the child, update its shortest paht estimate value
				// and its parent pointer
				if (newEstimate < ChildV -> GetSP()){

					ChildV -> SetShortestPathEstimate(newEstimate);
					ChildV -> SetVertexParent(ParentV);

				}//end if new estimate is less than current child estimate
			}

		}//end for e

	}// end for v

	// Bellman-Ford checking for negative-weight cycles
	bool NegCycle = false;

	for (int e=0; e<TtlE; e++){

		ParentV = EdgeArr[e]->GetParent();
		ChildV = EdgeArr[e] -> GetChild();

		if (ChildV -> GetSP() > ParentV -> GetSP() + EdgeArr[e] -> GetWeight()){
		
			NegCycle = true;

		}

	}

	// If there is a negative cycle, return an empty vector
	if (!NegCycle){

		// Start from the Target vertex and obtain the parent pointer up to the source, adding them 
		// to the stack
		Vertex* CurrentPointer = Target;

		while (CurrentPointer != nullptr){
			
			//Add the current vertex pointer to the stack
			ReversedShortestPath.push(CurrentPointer);

			CurrentPointer = CurrentPointer -> GetParentPntr();

		}// end while

		// Pop and add the coordinates to the return vector
		std::tuple<int,int> Coordinates;

		while(ReversedShortestPath.size() > 0){

			Coordinates = ReversedShortestPath.top() -> GetCoord();
			RtrnVec.push_back(Coordinates);
			ReversedShortestPath.pop();

		}// end while

	}// end if negative cycle
	
	return RtrnVec;

}// end FindShortestPath
