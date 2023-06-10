# PGM UTILITIES
A series of programs which can be used to edit PGM files.

# INSTRUCTIONS
Run 'make' to initalise all executables

./pgmEcho input output - Duplicates the input file into the output file

./pgmComp input input2 - Returns output depending on whether the inputs are the same

./pgma2b input ouput - Converts an ascii pgm file to a binary pgm file

./pgmb2a input ouput - Converts an binary pgm file to a ascii pgm file

./pgmReduce input factor output - Reduces the image's size and quality by the given factor

./pgmTile input factor output_template - Divides the image into factor x factor smaller images in a grid like fashion

./pgmAssemble output width height (row column input)+ - Merges many smaller images into one larger image
