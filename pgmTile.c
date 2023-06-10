/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>
#include <string.h>

//header file for prototypes, variables and the structure
#include "pgmImage.h"
#include "pgmTile.h"
//header file of error codes
#include "errorCodes.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: factor                 */
/* argv[3]: output file template   */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

pgmStruct pgmImage;

int main(int argc, char **argv)
{ /* main() */
	//Checks whether any arguments are entered
	if(argc == 1)	
	{
		printf("Usage: %s inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm\n", argv[0]);
		return EXIT_NO_ERRORS;
	}
	//Checks that the correct number of arguments are entered
	errorCheck = argumentCheck(argc, argv, 4);
	if (errorCheck != 0)
	{
		printf("ERROR: Bad Argument Count\n");
		return errorCheck;
	}
	//Scans in the factor for tiling
    sscanf(argv[2], "%d", &factor);
	//Creates a string for the file template
	char *fileTemplate = malloc (sizeof (char) * strlen(argv[3]));
	if (fileTemplate == NULL)
    {
        printf("ERROR: Image Malloc Failed\n");
        return EXIT_BAD_MALLOC;
    }
	fileTemplate = argv[3];
	//Reads in file
	errorCheck = readFile(argv[1]);
	if (errorCheck != 0)
		return errorCheck;
	//Checking that the factor is valid
	if(factor < 1 || factor > pgmImage.width || factor > pgmImage.height)
	{
		printf("ERROR: Miscellaneous invalid factor %d\n", factor);
		return EXIT_MISC;
	}
	//Returns the original file if the factor is one
	if(factor == 1)
	{
		fileName = malloc (sizeof (char) * 256);
		if (fileName == NULL)
    	{
        	printf("ERROR: Image Malloc Failed\n");
        	return EXIT_BAD_MALLOC;
    	}
		fileName = outputFormat(fileTemplate, 0, "<row>");
		//Uses 0 as the column value
		fileName = outputFormat(fileName, 0, "<column>");
		//Checking that the replacement worked
		if(strcmp(fileName, "#") == 0)
		{
			printf("ERROR: Miscellaneous (Bad template)\n");
			return EXIT_MISC;
		}
		writeFile(fileName);
	}
	else
	{
		//Splitting the width into an array where each element is an upper and lower bound of each section of the width
		int *widthSplit = malloc (sizeof (int) * (factor + 1));
		if (widthSplit == NULL)
    	{
        	printf("ERROR: Image Malloc Failed\n");
        	return EXIT_BAD_MALLOC;
    	}
		//Splitting the height in the same way
		int *heightSplit = malloc (sizeof (int) * (factor + 1));
		if (heightSplit == NULL)
    	{
        	printf("ERROR: Image Malloc Failed\n");
        	return EXIT_BAD_MALLOC;
    	}
		widthSplit = split(factor, pgmImage.width);
		heightSplit = split(factor, pgmImage.height);
		//Loops through all rows and columns of the new tiles
		for(int row = 0; row < factor; row++)
		{
			for(int col = 0; col < factor; col++)
			{
				sprintf(str, "%d", row);
				fileName = malloc (sizeof (char) * 256);
				if (fileName == NULL)
    			{
        			printf("ERROR: Image Malloc Failed\n");
        			return EXIT_BAD_MALLOC;
    			}
				//Replaces row with the row number
				fileName = outputFormat(fileTemplate, str, "<row>");
				if(strcmp(fileName, "#") == 0)
				{
					printf("ERROR: Miscellaneous (Bad template)\n");
					return EXIT_MISC;
				}
				//Replaces column with the column number
				sprintf(str, "%d", col);
				fileName = outputFormat(fileName, str, "<column>");
				if(strcmp(fileName, "#") == 0)
				{
					printf("ERROR: Miscellaneous (Bad template)\n");
					return EXIT_MISC;
				}

				//Opens the file to write t
				FILE *outputFile = fopen(fileName, "w");
				if (outputFile == NULL)
				{
					printf("ERROR: Bad File Name (%s)\n", fileName);
					return EXIT_BAD_FILE_NAME;
				}
	    		size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", widthSplit[col+1]-widthSplit[col], heightSplit[row+1]-heightSplit[row], pgmImage.maxGray);
				if (nBytesWritten < 0)
		    		return writeFailed(fileName);

				for (int i = heightSplit[row]; i < heightSplit[row+1]; i++)
				{ /* per gray value */
					for (int j = widthSplit[col]; j < widthSplit[col+1]; j++)
					{
						if(j == widthSplit[col+1] -1)
						{
							nBytesWritten = fprintf(outputFile, "%d%c", pgmImage.data2D[i][j],'\n');
						}
						else
						{
							nBytesWritten = fprintf(outputFile, "%d%c", pgmImage.data2D[i][j],' ');
						}
						if (nBytesWritten < 0)
		    				return writeFailed(fileName);
					}
				}
			}
		}
	}
	/* exiting with a success code */
	printf("TILED\n");
	return EXIT_NO_ERRORS;
} /* main() */

//Function for formatting the output format of the file
char *outputFormat(char template[256], char replace[128], char substr[128])
{
	char *output = malloc (sizeof (char) * 256);
    int templateIndex = 0, substrIndex = 0,i = 0, j = 0, flag = 0, start = 0;

    // check whether the substring to be replaced is present 
    while (template[templateIndex] != '\0')
    {
        if (template[templateIndex] == substr[substrIndex]) 
        {
            if (!flag)
                start = templateIndex;
            substrIndex++;
            if (substr[substrIndex] == '\0')
                break;
            flag = 1;
        } 
        else 
        {
            flag = start = substrIndex = 0;
        }
        templateIndex++;
    }
    if (substr[substrIndex] == '\0' && flag)
    {
        for (i = 0; i < start; i++)
            output[i] = template[i];

            //replace substring with another string 
            for (j = 0; j < strlen(replace); j++) 
            {
                output[i] = replace[j];
                i++;
            }
            //copy remaining portion of the input string "str" 
            for (j = start + strlen(substr); j < strlen(template); j++)
            {
                output[i] = template[j];
                i++;
            }
            // print the final string 
            output[i] = '\0';
        }
	else
	{
		return "#";
    }
    return output;
}