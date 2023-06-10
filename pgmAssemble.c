/***********************************/
/* Assembles tiles of a pgm file   */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

// library for modifiying strings
#include "string.h"

//header file for prototypes, variables and the structure
#include "pgmImage.h"
#include "pgmAssemble.h"
//header file of error codes
#include "errorCodes.h"

/***********************************/
/* main routine                    */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

pgmStruct pgmImage;

int main(int argc, char **argv)
{ /* main() */
    //Checks whether any arguments are entered
	if(argc == 1)	
	{
		printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+\n");
		return EXIT_NO_ERRORS;
	}
    /* check for correct number of arguments */
	if ((argc - 4) % 3 != 0)	
	{ /* wrong arg count */
		/* and return an error code      */
        printf("ERROR: Bad Argument Count\n");
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */

    //Finds the max row and column of the inputted tiles
    for(int i = 4; i < argc; i+= 3)
    {
        sscanf(argv[i], "%d", &tempRow);
        if(tempRow > maxRow)
            maxRow = tempRow;
        sscanf(argv[i+1], "%d", &tempCol);
        if(tempCol > maxCol)
            maxCol = tempCol;
    }
    //Scans in the inputted values for width and height of final file
    sscanf(argv[2], "%d", &maxWidth);
    sscanf(argv[3], "%d", &maxHeight);
    
    //Assigns memory for a 2D array to store the assembled image
    unsigned char ** outputData = (unsigned char **)malloc(maxHeight*sizeof(unsigned char *));
    for (int i = 0; i < maxHeight; i++)
	{
		outputData[i] = (unsigned char *)malloc(maxWidth);
		if(outputData[i] == NULL)
		{
			printf("ERROR: Image Malloc Failed");
			return EXIT_BAD_MALLOC;
		}
	}

    //Loops through all rows and cols or the tiles
    for(int i = 4; i < argc; i+=3)
    {
        //Reads in the rows and cols of the tiles
        sscanf(argv[i], "%d", &tempRow);
        sscanf(argv[i+1], "%d", &tempCol);

        errorCheck = readFile(argv[i+2]);
	    /* checking if error code is returned */
	    if (errorCheck != EXIT_NO_ERRORS)
		    return errorCheck;

        for(int i = 0; i < pgmImage.height; i++)
        {
            for(int j = 0; j < pgmImage.width; j++)
            {
                outputData[tempRow*maxHeight/(maxRow + 1)+i][tempCol*maxWidth/(maxCol + 1)+j] = pgmImage.data2D[i][j];
            }
        }
    }

    //Putting the assembled image data into variables to be written
    pgmImage.height = maxHeight;
    pgmImage.width = maxWidth;
    pgmImage.data2D = outputData;
    //Writes to the file
    errorCheck = writeFile(argv[1]);
    if(errorCheck != EXIT_NO_ERRORS)
    {
        return errorCheck;
    }
	/* exiting with a success code */
    printf("ASSEMBLED\n");
	return EXIT_NO_ERRORS;
} /* main() */

/*./pgmAssemble finish.pgm 512 512 0 0 input/bab_0_0.pgm 0 1 input/bab_0_1.pgm 0 2 input/bab_0_2.pgm 1 0 input/bab_1_0.pgm 1 1 input/bab_1_1.pgm 1 2 input/bab_1_2.pgm 2 0 input/bab_2_0.pgm 2 1 input/bab_2_1.pgm 2 2 input/bab_2_2.pgm*/

/*./pgmAssemble finish.pgm 512 512 0 1 input/bab_0_1.pgm 0 2 input/bab_0_2.pgm 1 0 input/bab_1_0.pgm 1 1 input/bab_1_1.pgm 1 2 input/bab_1_2.pgm 2 0 input/bab_2_0.pgm 2 1 input/bab_2_1.pgm 2 2 input/bab_2_2.pgm 0 0 input/bab_0_0.pgm*/

/*./pgmAssemble finish.pgm 512 512 0 0 input/bab_0_0.pgm 0 1 input/bab_0_1.pgm 0 2 input/bab_0_2.pgm 1 0 input/bab_1_0.pgm 1 1 input/bab_1_1.pgm 1 2 input/bab_1_2.pgm 2 0 input/bab_2_0.pgm 2 1 input/bab_2_1.pgm 2 2 input/bab_2_2.pgm 0 3 input/bab_0_3.pgm 1 3 input/bab_1_3.pgm 2 3 input/bab_2_3.pgm 3 3 input/bab_3_3.pgm 3 0 input/bab_3_0.pgm 3 1 input/bab_3_1.pgm 3 2 input/bab_3_2.pgm*/
