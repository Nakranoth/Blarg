/*****************************************************
*
*
******************************************************/

#include"Tile.h"

Tile::Tile(int a, int b)
{
	type = a;
	switch(a)
	{
		case tEmpty:
			tileType = "tEmpty";
			break;
		case tGround:
			tileType = "tGround";
			break;
		case tWall:
			tileType = "tWall";
			break;
		case tFloor: 
			tileType = "tFloor";
			break;
		case tDoorFrame:
			tileType = "tDoorFrame";
			break;
		case tWindowFrame:
			tileType = "tWindowType";
			break;
		case tPath:
			tileType = "tPath";
			break;
		case tRoad:
			tileType = "tRoad";
			break;
		default:
			tileType = "tUndefined";
	}
}

Tile::Tile()
{
}

int Tile::addOn(int type, void* add)
{
	int size = whatsOnMe[1].size();
	whatsOnMe[type][size];
	return 1;
}


