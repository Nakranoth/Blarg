/**
*	This is the primary file for Blarg,, it will serve to provide us with 
*	our initialization and main program loop.
*	
*	Contributers: Nathan Killeen
*	Last Modified: October 16, 2009
*/

#include "building.h"
#include "enums.h"

#include <iostream>
#include <time.h>
#include <cstdlib>
 
 
void genMap(){
	building* map = new building(50,25,1);
	//map->seed();
/*	building* road = new building(0,48,0,100,4,1);
	road->setFill(tRoad);
	road->init();
	map->addRoom(road);
	map->init();
	map->printMap();*/
//*	
	building* house = new building(10,15,1);
	house->setFill(tFloor);
	house->setWall(tWall);
	building* room = new building(5,8,1);
	room->setFill(tFloor);
	room->setWall(tWall);
	//std::cout << "roomdone?\n";
	house->addRoom(room);
	//std::cout << "housedone?\n";
	map->addRoom(house);
	//std::cout << "MapAdd?\n";
//*/
	room->init();
	house->init();
	house->printMap();
	map->init();
//std::cout << "MapDone?\n";
	map->printMap();
	delete map;
}

int main(){
	static const int SEED = (unsigned)time(NULL);
	srand(SEED);
	genMap();
} 