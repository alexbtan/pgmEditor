/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

//Defining a struct
typedef struct 
{
    /* the magic number		         */
    /* stored as two bytes to avoid	         */
    /* problems with endianness	         */
    /* Raw:    0x5035 or P5		         */
    /* ASCII:  0x5032 or P2		         */
    unsigned char magic_number[2];
    unsigned short *magic_Number;

    /* we will store ONE comment	         */
    char *commentLine;

    /* the logical width & height	         */
    /* note: cannot be negative	         */
    unsigned int width, height;

    /* maximum gray value (assumed)	         */
    /* make it an integer for ease	         */
    unsigned int maxGray;

    //2D array for image data
    unsigned char ** data2D;
} pgmStruct;

//Declaring a struct
extern pgmStruct pgmImage;

int errorCheck;
//Prototypes
int readFile(char * fileName);
int initialseImage();
int readHeader(FILE *inputFile, char * fileName);
int binaryRead(FILE *inputFile, char * fileName);
int asciiRead(FILE *inputFile, char * fileName);
int imageDataFailed(FILE *inputFile);
int writeFile(char * fileName);
int writeFileBinary(char * fileName);
int writeFailed();
int argumentCheck(int argc, char **argv, int argNum);
int isEmpty(unsigned char **data2D, FILE *inputFile, char *fileName);
