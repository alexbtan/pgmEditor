//Writes data to an output file in ascii pgm
#include <stdio.h>
#include <stdlib.h>
#include "errorCodes.h"
#include "pgmImage.h"

int writeFile(char * fileName)
{
	//Opens file to be written to
	FILE *outputFile = fopen(fileName, "w");

	/* check whether file opening worked     */
	if (outputFile == NULL)
	{
		printf("ERROR: Bad File Name (%s)\n", fileName);
		return EXIT_BAD_FILE_NAME;
	}
	
	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", pgmImage.width, pgmImage.height, pgmImage.maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
		writeFailed(fileName);

    /* pointer for efficient write code      */
	for (int i = 0; i < pgmImage.height; i++)
	{ /* per gray value */
		for (int j = 0; j < pgmImage.width; j++)
		{ /* per gray value */
			/* get next char's column        */
		int nextCol = pgmImage.width - j - 1;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(outputFile, "%d%c",pgmImage.data2D[i][j], (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (nBytesWritten < 0)
			return writeFailed(fileName);
		} /* per gray value */
	} /* per gray value */
	return EXIT_NO_ERRORS;
}

int writeFileBinary(char * fileName)
{
	//Opens file to be written to
	FILE *outputFile = fopen(fileName, "wb");

	/* check whether file opening worked     */
	if (outputFile == NULL)
		return writeFailed(fileName);
	
	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P5\n%d %d\n%d\n", pgmImage.width, pgmImage.height, pgmImage.maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
		return writeFailed(fileName);

    /* writes image data                     */
	for (int i = 0; i < pgmImage.height; i++)
	{
		nBytesWritten = fwrite(pgmImage.data2D[i], 1, pgmImage.width, outputFile);
		/* sanity check on write         */
		if (nBytesWritten < 0)
			return writeFailed(fileName);
	}
	return EXIT_NO_ERRORS;
}

int writeFailed(char * fileName)
{
	/* free memory           */
	free(pgmImage.commentLine);
	free(pgmImage.data2D);

	printf("ERROR: Output Failed (%s)\n", fileName);
	return EXIT_BAD_OUTPUT;
}