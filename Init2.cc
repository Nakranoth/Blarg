/****************************************************
 * 
 * 
 * 
 * **************************************************/

#include"Init.h"


int main(int argc, char* argv[])
{ ////////////// modify to two classes, one to create the 3d int array, 
  //////////////and one to take it in and create the tileMap(int*** array, int width, int depth, int height).
	char varW[MAX_LINE];
	char varH[MAX_LINE];
	char varS[MAX_LINE];
	
	cin >> varH >> varW;
	cin.getline(varS, '\n');

	int tempMap[atoi(varW)][atoi(varH)];
	Tile* map[atoi(varW)][atoi(varH)];
	int tileCount = 0;
	
	
	for(int i = 0; i < atoi(varH); i++)
	{
		for(int j = 0; j < atoi(varW); j++)
		{
			int sneaky;
			map[i][j] = new Tile((((sneaky = fgetc(stdin)) == 10 ? fgetc(stdin):sneaky) - 48), i);
			cout << map[i][j]->type;
			tileCount ++;
		}
	    	cout << endl;
	}
}
