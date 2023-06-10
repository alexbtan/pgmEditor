 /***********************************/
/* Compares two pgm files to see if*/
/* they are logically identical    */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>
/* library for string routines     */
#include <string.h>

/* library for memory routines     */
#include <stdlib.h>

//header file for prototypes, variables and the structure
#include "pgmComp.h"
#include "pgmImage.h"
//header file of error codes
#include "errorCodes.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: first input file name  */
/* argv[2]: second input file name */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

//Defines the image structure
pgmStruct pgmImage;

int main(int argc, char **argv)
{ /* main() */
	if(argc == 1)	
	{
		printf("Usage: %s inputImage.pgm inputImage.pgm\n", argv[0]);
		return EXIT_NO_ERRORS;
	}
	//Checks that the number of arguments given is correct 
	errorCheck = argumentCheck(argc, argv, 3);
	//Checks if an error code is returned
	if (errorCheck != EXIT_NO_ERRORS)
	{
		/* print an error message        */
		printf("ERROR: Bad Argument Count\n");
		return errorCheck;
	}
	//Reads the data from the first file in
	int errorCheck = readFile(argv[1]);
	//Checks if an error code is returned
	if (errorCheck != EXIT_NO_ERRORS)
		return errorCheck;

	//Stores the information to compare about the first file
	height2 = pgmImage.height;
	width2 = pgmImage.width;
	maxGray2 = pgmImage.maxGray;
	data2D2 = pgmImage.data2D;

	//Reads the data from the second file in
	errorCheck = readFile(argv[2]);
	//Checks if an error code is returned
	if (errorCheck != EXIT_NO_ERRORS)
		return errorCheck;

	//Compares the two images and outputs an according message
	if (height2 == pgmImage.height && width2 == pgmImage.width && pgmImage.maxGray == maxGray2)
	{
		for(int i = 0; i < pgmImage.height; i++)
		{
			if(memcmp(pgmImage.data2D[i], data2D2[i], pgmImage.width) != 0)
			{
				printf("DIFFERENT\n");
				/* exiting with a success code */
				return EXIT_NO_ERRORS;
			}
		}
		printf("IDENTICAL\n");
		/* exiting with a success code */
		return EXIT_NO_ERRORS;
	}
	printf("DIFFERENT\n");
	/* exiting with a success code */
	return EXIT_NO_ERRORS;
} /* main() */