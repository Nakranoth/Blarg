/**
*Header file for the map and all contained buildings.
*
*Contributers: Nathan Killeen
*/

#ifndef building__		//prevents re-declaration of building
#define building__


#include <queue>
	//For children storage.
#include <cstdlib>
	//For random numbers.
//#include <time.h>
	//For Time based seeds
#include "enums.h"

class building{
	public:
		int x,y,z,				//stores relative position within parent. May be used by the parent to determine children's internal position.
		width, depth, height,	//stores internal size of the grid. Used to determine the size of map.
		fill,wall,air;			//stores the tile_type to be used to fill the room. 
		int ***map;				//refrence to 3d array. Will store tile info.
		bool ***bmap;			//refrence to 3d array. Will store tile filled state.
	private:
		std::queue<building*> contains;	//contains all children of this room/building.
		//static int SEED;	//World generation seed. Constant now for debugging.
	public:
		//constructors
		building(int _x, int _y, int _z, int _width, int _depth, int _height);

		building(int _width, int _depth, int _height);
		
		~building();
		
		void seed(int SEED);			// seeds the random number generator;
		void addRoom(building* a);		// adds a child to this building
		void merge(building* a, building* b);	// connects children a and b inside building.
		void merge(building* a, building* b, int orient);	// connects children a and b inside building using orientation. 
		void printMap();	//text output of file.
		void setFill(int tType);
		void setWall(int tType);
		void setAir(int tType);
		void init(int orient = EDGE);	//makes the building, merging it's floor map with it's children's, then deleting the children. Assumes edge as default. 
	private:
		void allokMap();
		void deallokMap();
		void allokBMap();
		void deallokBMap();
		void handle(building* a, int orient);
		void addToSelf(building* a, int xh, int yh, int zh);
		const int varToConst(int in);
};

#endif
