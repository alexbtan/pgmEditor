/***********************************/
/* A first iteration to take a pgm */
/* file in binary and convert to   */
/* ASCII or vice versa             */
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
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

//Defines the image structure
pgmStruct pgmImage;

int main(int argc, char **argv)
	{ /* main() */
	if(argc == 1)
	{
		printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
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
	//Reads in data from the file
	errorCheck = readFile(argv[1]);
	//Checks if an error is returned
	if (errorCheck != 0)
		return errorCheck;
	//Writes the data to a file
	errorCheck = writeFile(argv[2]);
	//Checks if an error is returned
	if (errorCheck != 0)
		return errorCheck;
	/* exiting with a success code */
	printf("ECHOED\n");
	return EXIT_NO_ERRORS;
} /* main() */