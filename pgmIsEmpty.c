//Checks if a files imageData is empty
#include <stdio.h>
#include <stdlib.h>
#include "errorCodes.h"
#include "pgmImage.h"

int isEmpty(unsigned char **data2D, FILE *inputFile, char *fileName)
{
	if (pgmImage.data2D == NULL)
		{ /* malloc failed */
		/* free up memory                */
		free(pgmImage.commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Data (%s)\n", fileName);	
		
		/* return error code             */
		return EXIT_BAD_DATA;
		} /* malloc failed */
	return EXIT_NO_ERRORS;
}