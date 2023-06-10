//File to read in a pgm file in either binary or ascii
/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>
#include "errorCodes.h"
#include "pgmImage.h"
//Include module to check if the file is empty

//Reads in the file 
int readFile(char * fileName)
{
	initialseImage();
	//Opens the file
	FILE *inputFile = fopen(fileName, "rb");
	//Error for a non readable file
	if (inputFile == NULL)
	{
		printf("ERROR: Bad File Name (%s)\n", fileName);
		return EXIT_BAD_FILE_NAME;
	}
	//Reads in header
	errorCheck = readHeader(inputFile, fileName);
	if(errorCheck != EXIT_NO_ERRORS)
		return errorCheck;
	/* reads the file in binary if the magic number is for binary files   */
	if(*pgmImage.magic_Number == MAGIC_NUMBER_RAW_PGM)
	{	
		//Reads in the file in binary and checks for any errors returned
		errorCheck = binaryRead(inputFile, fileName);
		if(errorCheck != EXIT_NO_ERRORS)
			return errorCheck;
	}
	/* reads the file in binary if the magic number is for ascii files   */
	else if(*pgmImage.magic_Number == MAGIC_NUMBER_ASCII_PGM)
	{
		errorCheck = asciiRead(inputFile, fileName);
		if(errorCheck != EXIT_NO_ERRORS)
			return errorCheck;
	}
	//Return error for any other magic number
	else
	{
		imageDataFailed(inputFile);
		printf("ERROR: Bad Magic Number (%s)\n", fileName);
		return EXIT_BAD_MAGIC_NUMBER;
	}
	//Check to ensure there isn't too much data
	char nextChar = fgetc(inputFile);
	while(nextChar != EOF)
	{
		if(nextChar != '\n' && nextChar != ' ')
		{
			printf("ERROR: Bad Data (%s)\n", fileName);
			return EXIT_BAD_DATA;
		}
		nextChar = fgetc(inputFile);
	}
	/* we're done with the file, so close it */
	fclose(inputFile);
	return EXIT_NO_ERRORS;	
}

//Reads in the ascii header of a file
int readHeader(FILE *inputFile, char * fileName)
{
	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");
	/* read in the magic number              */
	pgmImage.magic_number[0] = getc(inputFile);
	pgmImage.magic_number[1] = getc(inputFile);
	/* scan whitespace if present            */
	scanCount = fscanf(inputFile, " ");

	/* check for a comment line              */
	char nextChar = fgetc(inputFile);
	if (nextChar == '#')
	{ /* comment line                */
		/* allocate buffer               */

		//Checking length of comment
		int count = 0;
		while(nextChar != '\n')
		{
			nextChar = fgetc(inputFile);
			count += 1;
		}
		//Checks if the comment is too large
		if(count > MAX_COMMENT_LINE_LENGTH)
		{
			printf("ERROR: Bad Comment Line (%s)\n", fileName);
			return EXIT_BAD_COMMENT_LINE;
		}
		//Checks if comment is empty
		if (count == 0)
		{ 
			imageDataFailed(inputFile);
			printf("ERROR: Bad Comment Line (%s)\n", fileName);
			return EXIT_BAD_COMMENT_LINE;
		} 
	} /* comment line */
	else
	{ /* not a comment line */
		/* put character back            */
		ungetc(nextChar, inputFile);
	} /* not a comment line */

	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
	scanCount = fscanf(inputFile, " %u %u %u", &(pgmImage.width), &(pgmImage.height), &(pgmImage.maxGray));
	/* sanity checks on size & grays         */
	/* must read exactly three values        */
	if 	(
		(scanCount != 3) ||
		(pgmImage.width < MIN_IMAGE_DIMENSION) ||
		(pgmImage.width > MAX_IMAGE_DIMENSION) ||
		(pgmImage.height < MIN_IMAGE_DIMENSION) ||
		(pgmImage.height > MAX_IMAGE_DIMENSION) 
		)
	{
		imageDataFailed(inputFile);
		printf("ERROR: Bad Dimensions (%s)\n", fileName);
		return EXIT_BAD_DIMENSIONS;
	}
	//Sanity check on max gray
	if (pgmImage.maxGray != 255)
	{
		imageDataFailed(inputFile);
		printf("ERROR: Bad Max Gray Value (%s)\n", fileName);
		return EXIT_BAD_MAX_GRAY;
	}
	/* allocate the data array             */
	pgmImage.data2D = (unsigned char **)malloc(pgmImage.height*sizeof(unsigned char *));
    for (int i = 0; i < pgmImage.height; i++)
	{
		pgmImage.data2D[i] = (unsigned char *)malloc(pgmImage.width*2);
		if(pgmImage.data2D[i] == NULL)
		{
			printf("ERROR: Image Malloc Failed");
			return EXIT_BAD_MALLOC;
		}
	}

	if(pgmImage.data2D == NULL)
	{
		printf("ERROR: Image Malloc Failed");
		return EXIT_BAD_MALLOC;
	}

	/* sanity check for memory allocation    */
	errorCheck = isEmpty(pgmImage.data2D,inputFile, fileName);
	if(errorCheck != EXIT_NO_ERRORS)
		return errorCheck;

	return EXIT_NO_ERRORS;	
}

//Reads in the file if it is in binary pgm
int binaryRead(FILE *inputFile, char * fileName)
{
	//Reads in the buffer
	int buffer[1];
	fread(buffer, 1, 1, inputFile);
	
	// sanity check
	for (int j = 0; j < pgmImage.height; j++)
	{ 

		//Reads in all the imageData of the file
		int scanCount = fread(pgmImage.data2D[j], 1, pgmImage.width, inputFile);

		if (scanCount != pgmImage.width)
		{
			imageDataFailed(inputFile);
			printf("ERROR: Bad Data (%s)\n", fileName);
			return EXIT_BAD_DATA;
		}
	}
	//Loops through all the image data
	for (int i = 0; i < pgmImage.height; i++)
	{
		for (int j = 0; j < pgmImage.width; j++)
		{ 
			/* sanity check	                 */
			if ((pgmImage.data2D[i][j] < 0) || (pgmImage.data2D[i][j] > pgmImage.maxGray))
			{
				imageDataFailed(inputFile);
				printf("ERROR: Bad Data (%s)\n", fileName);
				return EXIT_BAD_DATA;
			}
		} 
	}
	return EXIT_NO_ERRORS;
}

//Reads in the file if it is in ascii pgm
int asciiRead(FILE *inputFile, char * fileName)
{
	//Reads in all the data
	for (int i = 0; i < pgmImage.height; i++)
	{ 
		for (int j = 0; j < pgmImage.width; j++)
		{ 
			int grayValue = -1;
			int scanCount = fscanf(inputFile, " %u", &grayValue);
			/* sanity check	                 */
			if ((scanCount != 1) || (grayValue < 0) || (grayValue > pgmImage.maxGray))
			{
				imageDataFailed(inputFile);
				printf("ERROR: Bad Data (%s)\n", fileName);
				return EXIT_BAD_DATA;
			}
			/* set the pixel value           */
			pgmImage.data2D[i][j] = (unsigned char) grayValue;
		} 
	} 
	return EXIT_NO_ERRORS;
}

int imageDataFailed(FILE *inputFile)
{
	/* free memory           */
	free(pgmImage.commentLine);
	free(pgmImage.data2D);	

	/* close file            */
	fclose(inputFile);
}

int initialseImage()
{
	//Initialise struct data
	pgmImage.magic_number[0] = '0';
	pgmImage.magic_number[1] = '0';
	pgmImage.magic_Number = (unsigned short *) pgmImage.magic_number;
	pgmImage.commentLine = NULL;
	pgmImage.width = 0, pgmImage.height = 0;
	pgmImage.maxGray = 255;
	pgmImage.data2D = NULL;
}