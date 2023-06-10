/***********************************/
/* Compresses a pgm file           */
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
#include "pgmReduce.h"
//header file of error codes
#include "errorCodes.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: reduction factor       */
/* argv[3]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

//Declares a structure
pgmStruct pgmImage;

int main(int argc, char **argv)
{ /* main() */
	//Checks for empty call
	if(argc == 1)
	{
		//Prints usage message
		printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
		return EXIT_NO_ERRORS;
	}
	//Checks the number of arguments is correct
	errorCheck = argumentCheck(argc, argv, 4);
	if (errorCheck != 0)
	{
		/* print an error message        */
		printf("ERROR: Bad Argument Count\n");
		return errorCheck;
	}
	//Reads in the reduction factor
  	sscanf(argv[2], "%d", &factor);
	//Reads in the file and checks that no errors occur
	errorCheck = readFile(argv[1]);
	if (errorCheck != 0)
	{
		return errorCheck;
	}
	//Returns error code for invalid factor
	if(factor < 1 || factor > pgmImage.width || factor > pgmImage.height)
	{
		printf("ERROR: Miscellaneous invalid factor %d\n", factor);
		return EXIT_MISC;
	}
	//Returns base file if the compression factor is 1
	if(factor == 1)
		writeFile(argv[3]);
	else
	{
		//Opens the output file
		FILE *outputFile = fopen(argv[3], "w");
		/* check whether file opening worked     */
		if (outputFile == NULL)
		{
			printf("ERROR: Bad File Name (%s)\n", argv[3]);
			return EXIT_BAD_FILE_NAME;
		}
		//Outputs the header details
		size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", (pgmImage.width - 1) / factor + 1, (pgmImage.height - 1) / factor + 1, pgmImage.maxGray);
		if (nBytesWritten < 0)
			return writeFailed(argv[3]);

		//Loops through all required data
		for (int i = 0; i < pgmImage.height; i+=factor)
		{ 
			for (int j = 0; j < pgmImage.width; j+=factor)
			{ 
				//Inputs the data into the new file
				nBytesWritten = fprintf(outputFile, "%d%c", pgmImage.data2D[i][j],' ');
				if (nBytesWritten < 0)
					return writeFailed(argv[3]);
			}
			nBytesWritten = fprintf(outputFile, "\n");
		}
	}
	/* exiting with a success code */
	printf("REDUCED\n");
	return EXIT_NO_ERRORS;
} /* main() */