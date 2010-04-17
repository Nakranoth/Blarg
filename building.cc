#include "building.h"
#include <assert.h>
#include <iostream>

building::building(int _x, int _y, int _z, int _width, int _depth, int _height): x(_x), y(_y), z(_z), width(_width), depth(_depth), height(_height){
	map = NULL;
	bmap = NULL;
	allokMap();
	fill = tGround;
	wall = tGround;
	air  = tEmpty;
}

building::building(int _width, int _depth, int _height): x(-1), y(-1), z(-1), width(_width), depth(_depth), height(_height){
	map = NULL;
	bmap = NULL;
	allokMap();
	fill = tGround;
	wall = tGround;
	air  = tEmpty;
}

building::~building(){
	deallokMap();
}

//PUBLIC FUNCTIONS

/**
*	Seeds the random number generator.
*/
void building::seed(int SEED){
	srand(SEED);
}

/*
*	Adds a building into this one's child queue
*/
void building::addRoom(building* a){
	contains.push(a);
}

void building::merge(building* a, building* b){

}

void building::merge(building* a, building* b, int orient){

}

void building::printMap(){
	for (int k = 0; k < height; k++){
		for (int j = depth - 1; j > 0; j--){
			for (int i = 0; i < width; i++){
				std::cout << map[i][j][k];
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}

void building::setFill(int tType){
	fill = tType;
}

void building::setWall(int tType){
	wall = tType;
}

void building::setAir(int tType){
	air = tType;
}

void building::init(int orient){
	//respect fills 
	for (int i = 0; i < width; i++){
		for (int j = 0; j < depth; j++){
			for (int k = 0; k < height; k++){
				if (k == 0)		//"ground" level should be a "floor"
					map[i][j][k]=fill;
				else
					map[i][j][k]=air;
			}
		}
	}
	if (!contains.empty()){
		if (contains.front() != contains.back()){	//Has more than 1 child.
			allokBMap();
			//retrieve children
			while(!contains.empty()){
				handle(contains.front(),orient);	//Adds the children.
				delete contains.front();
				contains.front()=NULL;
				contains.pop();
			}
			deallokBMap();
		}
		else{
			handle(contains.front(),orient);
	//std::cout << "BLAH!\n";
			delete contains.front();
			contains.front()=NULL;
			contains.pop();
	//std::cout << "BLAH2!\n";
		}
	}
}


//PRIVATE FUNCTIONS

/*
*	Allocates memory for the map.
*/
void building::allokMap(){
	assert(map==NULL);
	map = new int [varToConst(width)][varToConst(depth)][varToConst(height)]; //probably doesn't work.
	//std::cout << height << '\n';
	/*map = new int**[width];
	for (int i = 0; i < width;i++){
		//std::cout << '\n' << depth << ": " << i << '\n';
		map[i] = new int*[depth];
		for (int j = 0; j<depth;j++){
			//std::cout << '\n' << width << ": " << j << '\n';
			map[i][j]=new int[height];
			for (int k = 0; k < height; k++){
				map[i][j][k] = tEmpty;
			}
		}
	}*/
	
}

/*
*	Hopefully frees the memory from the map.
* 	If it works properly, it should prevent memory leaks. 
*/
void building::deallokMap(){
	assert(map != NULL);
	for (int i = 0; i < width;i++){
		for (int j = 0; j<depth;j++){
	//std::cout <<i<<' '<< j<< ' ' << width << ' ' << depth << ' ' << height << ',' << map[i][j][0]<< ' ' << sizeof map[i][j] << "\n";
			delete [] map[i][j];
			map[i][j]=NULL;
		}
		delete [] map[i];
		map[i]=NULL;
	//std::cout << i<<"\n";
	}
	delete [] map;
	map = NULL;
	//std::cout << "151?\n";
}

/*
*	Allocates memory for the boolean map.
*/
void building::allokBMap(){
	assert(bmap==NULL);
	//std::cout << height << '\n';
	bmap = new bool**[width];
	for (int i = 0; i < width;i++){
		//std::cout << '\n' << depth << ": " << i << '\n';
		bmap[i] = new bool*[depth];
		for (int j = 0; j<depth;j++){
			//std::cout << '\n' << width << ": " << j << '\n';
			bmap[i][j]=new bool[height];
			for (int k = 0; k < height; k++){
				map[i][j][k] = false;
			}
		}
	}
}

/*
*	Hopefully frees the memory from the boolean map.
* 	If it works properly, it should prevent memory leaks. 
*/
void building::deallokBMap(){
	assert(bmap != NULL);
	for (int i = 0; i < width;i++){
		for (int j = 0; j<depth;j++){
			delete [] bmap[i][j];
		}
		delete [] bmap[i];
	}
	delete [] bmap;
	bmap = NULL;
}

/**
*	Handles merging a child with this parent.
*	Orient decides if children should be added from the corners.
*		EDGE means rooms should be added space efficiently.
		RANDOM means rooms should be added completely randomly. Used for roads, etc. 
*/
void building::handle(building* a, int orient){
	int maxX = width - a->width,
	maxY = depth - a->depth,
	maxZ = height - a->height;	//valid maximum values for new child.
	bool xSp = (a->x >= 0), ySp = (a->y >= 0), zSp = (a->z >= 0);	//boolean for weather a dimensional location is specified.
	
	if (bmap == NULL){	//only one child. Add it wherever.
		if (xSp && ySp && zSp){	//Exact location specified
			if	(a->x > maxX || a->y > maxY || a->z > maxZ){std::cout << "Invalid position for child.";}// << a->x << ',' << a->y << ' ' << a->width << ',' << a->depth << " in " << width << ' ' << depth << ' ' << maxX << ' ' << maxY << '\n';}
			else{
				addToSelf(a,a->x,a->y,a->z);
			}
		}
		else{
			int mx = rand();
			assert(mx!=0);
			if (!xSp&&maxX>0)	a->x = mx % maxX;
			assert(mx = rand()!=0);
			if (!ySp&&maxY>0)	a->y = mx % maxY;
			assert(mx = rand()!=0);
			if (!zSp&&maxZ>0)	a->z = mx % maxZ;
			if (orient == EDGE){
				if(xSp^ySp^zSp == 1 || !(xSp|ySp|zSp)){	//exactly one or none defined. (Can't be all three b/c it's already handled.) Try a corner, rotate if invalid.
					int corner = rand() % 8;	//enum topbackleft, clockwise, bottombackleft, clockwise
					bool solved = false;
					//int maxX = width - a->width;
					//int maxY = depth - a->depth;
					//int maxZ = height - a->height;
					for (int i = 0; i < 8; i++){
						switch (corner){
							case 0:	//tbl
								if ((!xSp || a->x == 0)&&(!ySp || a->y == maxY)&&(!zSp || a->z == maxZ)){
									a-> x = 0;
									a-> y = maxY;
									a-> z = maxZ;
									solved = true;
								}
								else{corner++;}
								break;
							case 2://tbr
								if ((!xSp || a->x == maxX)&&(!ySp || a->y == maxY)&&(!zSp || a->z == maxZ)){
									a-> x = maxX;
									a-> y = maxY;
									a-> z = maxZ;
									solved = true;
								}
								else{corner++;}
								break;
							case 4://tfr
								if ((!xSp || a->x == maxX)&&(!ySp || a->y == 0)&&(!zSp || a->z == maxZ)){
									a-> x = maxX;
									a-> y = 0;
									a-> z = maxZ;
									solved = true;
								}
								else{corner++;}
								break;
							case 6://tfl
								if ((!xSp || a->x == 0)&&(!ySp || a->y == 0)&&(!zSp || a->z == a->height)){
									a-> x = 0;
									a-> y = 0;
									a-> z = maxZ;
									solved = true;
								}
								else{corner++;}
								break;
							case 5://bbl
								if ((!xSp || a->x == 0)&&(!ySp || a->y == maxY)&&(!zSp || a->z == 0)){
									a-> x = 0;
									a-> y = maxY;
									a-> z = 0;
									solved = true;
								}
								else{corner++;}
								break;
							case 7://bbr
								if ((!xSp || a->x == maxX)&&(!ySp || a->y == maxY)&&(!zSp || a->z == 0)){
									a-> x = maxX;
									a-> y = maxY;
									a-> z = 0;
									solved = true;
								}
								else{corner++;}
								break;
							case 1://bfr
								if ((!xSp || a->x == maxX)&&(!ySp || a->y == 0)&&(!zSp || a->z == 0)){
									a-> x = maxX;
									a-> y = 0;
									a-> z = 0;
									solved = true;
								}
								else{corner++;}
								break;
							case 3://bfl
								if ((!xSp || a->x == 0)&&(!ySp || a->y == 0)&&(!zSp || a->z == 0)){
									a-> x = 0;
									a-> y = 0;
									a-> z = 0;
									solved = true;
								}
								else{corner=0;}
								break;
							//Always at least a diagonal from the previous. Alternates diagonal and opposite.
						}
					}
				}
				else {	//2 defined
					if (xSp&ySp){	//z-to edge
						if (rand()%2)	// ==1
							a->z=height - a->height;
						else
							a->z=0;
					}
					else if (xSp&zSp){	//y-to edge
						if (rand()%2)	// ==1
							a->y=depth - a->depth;
						else
							a->y=0;
					}
					else{
						if (rand()%2)	// ==1
							a->x=width - a->width;
						else
							a->x=0;
					}
				}
	//std::cout << "319?\n";
			}
		addToSelf(a,a->x,a->y,a->z);
		}
	}
}

/**
*	Directly adds the child. Location is determined by handle(building* a).
*/
void building::addToSelf(building* a, int xh, int yh, int zh){
	int maxX = width - a->width,
	maxY = depth - a->depth,
	maxZ = height - a->height;
	
	if	(xh > maxX || yh > maxY || zh > maxZ){std::cout << "Invalid position for child.";}
	
	for (int i = 0; i < a->width;i++){
		for (int j = 0; j < a->depth;j++){
			for (int k = 0; k < a->height;k++){
				if (i+xh >= width)	std::cout << "too wide: " << width << '\n';
				if (j+yh >= depth)	std::cout << "too deep: " << depth << '\n';
				if (k+zh >= height)	std::cout << "too tall: " << height << '\n'; 
				map[i+xh][j+yh][k+zh]	= int(a->map[i][j][k]);	//copys child's map into this map on the correct position.
				if (bmap != NULL)	bmap[i][j][k] = true;
			}
		}
	}
	if (a->wall != tEmpty){	//if it's supposed to be surrounded by something
		bool l = false,r = false,n = false,f = false;
		if (xh > 0)	l = true;	//has left wall
		if (yh > 0)	n = true;	//has near wall
		if (xh + a->width < width)	r = true;	//has right wall
		if (yh + a->depth < depth)	f = true;	//has far
		if (l)	for(int i = (0-n); i < (a->depth + f); i++)	for(int k = 0; k < a->height;k++){	//left wall
			map[xh-1][yh+i][k]=a->wall;
			if (bmap != NULL)	bmap[xh-1][yh+i][k] = true;			//Walls take up space.
		}	
		if (r)	for(int i = (0-n); i < (a->depth + f); i++)	for(int k = 0; k < a->height;k++){	//right wall
			map[xh+a->width][yh+i][k]=a->wall;
			if (bmap != NULL)	bmap[xh+a->width][yh+i][k] = true;	//Walls take up space.
		}
		if (n)	for(int i = 0; i < (a->width); i++)	for(int k = 0; k < a->height;k++){			//bottom wall
			map[xh+i][yh-1][k]=a->wall;
			if (bmap != NULL)	bmap[xh+i][yh-1][k] = true;			//Walls take up space.
		}	
		if (f)	for(int i = 0; i < (a->width); i++)	for(int k = 0; k < a->height;k++){			//bottom wall
			map[xh+i][yh+a->depth][k]=a->wall;
			if (bmap != NULL)	bmap[xh+i][yh+a->depth][k] = true;	//Walls take up space.
		}
	}
}


/*
* Ninja hacker maneuver to get an int const from an int.
*/
const int varToConst(int in){
	return in;
}