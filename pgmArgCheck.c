//Checks that the number of arguments given is the same as is intended
#include "errorCodes.h"
#include "pgmImage.h"

int argumentCheck(int argc, char **argv, int argNum)
{
	/* check for correct number of arguments */
	if (argc != argNum)	
	{ /* wrong arg count */
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */
	return EXIT_NO_ERRORS;
}