#include "errorCodes.h"
#include "pgmImage.h"

//Function to split the width into different parts
int * split(int factor, int dimension)
{
	int totalDimension = dimension;
	int remainFactor = factor;
	int *tileSplit = malloc (sizeof (int) * (factor + 1));
	tileSplit[0] = 0;
	//Loops through each sector of the width
	for (int i = 1; i < factor; i++)
	{
		//Calulcates the next upper band of the sector
		tileSplit[i] = tileSplit[i-1] + dimension/remainFactor;
		dimension -= dimension/remainFactor;
		remainFactor--;
	}
	tileSplit[factor] = totalDimension;
	return tileSplit;
}