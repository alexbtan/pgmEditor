/***********************************/
/* Takes in a binary file          */
/* and outputs an equivalent ascii */
/* file                            */    
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

//header file for prototypes, variables and the structure
#include "pgmImage.h"
//header file of error codes
#include "errorCodes.h"


/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: binary file name       */
/* argv[2]: ascii file name        */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

pgmStruct pgmImage;

int main(int argc, char **argv)
{ /* main() */
	if(argc == 1)	
	{
		printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
		return EXIT_NO_ERRORS;
	}
	errorCheck = argumentCheck(argc, argv, 3);
	/* checking if error code is returned */
	if (errorCheck != 0)
	{
		printf("ERROR: Bad Argument Count\n");
		return errorCheck;
	}
	errorCheck = readFile(argv[1]);
	/* checking if error code is returned */
	if (errorCheck != EXIT_NO_ERRORS)
		return errorCheck;
	if(pgmImage.magic_number[1] != '5')
	{
		printf("ERROR: Bad Magic Number (%s)\n", argv[1]);
		return EXIT_BAD_MAGIC_NUMBER;
	}
	errorCheck = writeFile(argv[2]);
	/* checking if error code is returned */
	if (errorCheck != EXIT_NO_ERRORS)
		return errorCheck;
	/* exiting with a success code */
	printf("CONVERTED\n");
	return EXIT_NO_ERRORS;
} /* main() */