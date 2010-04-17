/**
*Header file for the enumerators used for the map generator.
*
*Contributers: Nathan Killeen
*/

#ifndef enums__
#define enums__

enum tile_type{
	tEmpty, tGround, tWall, tFloor, tDoorFrame, tWindowFrame, tPath, tRoad
};

enum orentation{
	TOP,BOTTOM,LEFT,RIGHT,DEEP,NEAR
};

enum position{
	RAND, EDGE, CENTER
};

#endif