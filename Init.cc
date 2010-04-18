/****************************************************
 * 
 * 
 * 
 * **************************************************/

#include"Init.h"

/*
class Init
{
	Init();
};
*/


int main(int argc, char* argv[])
{
	char varW[MAX_LINE];
	char varH[MAX_LINE];
	char varS[MAX_LINE];
	
	cin >> varH >> varW;
	cin.getline(varS, '\n');

	int tempMap[atoi(varW)][atoi(varH)];
	Tile* map[atoi(varW)][atoi(varH)];
	int tileCount = 0;
	
    
	for(int i = 0; i < atoi(varH); i++)
		for(int j = 0; j < atoi(varW); j++)
		{
			int sneaky;
			tempMap[i][j] = (((sneaky = fgetc(stdin)) == 10 ? fgetc(stdin):sneaky) - 48);
			tileCount ++;
		}
    
	for(int i = 0; i < atoi(varH); i++){
		for(int j = 0; j < atoi(varW); j++)
		{
			cout << tempMap[i][j];
			map[i][j] = new Tile(tempMap[i][j],j);
		}
			cout << endl;}
			
	cout << endl << endl;
	
	
	for(int i = 0; i < atoi(varH); i++)
	{
		for(int j = 0; j < atoi(varW); j++)
		{
			cout << map[i][j]->type;
		}
			cout << endl;
	}
	
}
