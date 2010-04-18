/******************************************************
 * 
 * 
 * 
 * ****************************************************/
#ifndef _TILE_H_
#define _TILE_H_


#include<vector>
#include<string>
#include"enums.h"

using namespace std;

class Tile
{
	private:
		vector<void*> whatsOnMe[]; // creatures stored in 0, items in 1, interactables in 2
	
	public:
		Tile(int, int);
		Tile();
		string tileType;
		int type;
		int addOn(int, void*); // used to add to the tile's list of what is on top of it	
};
#endif
