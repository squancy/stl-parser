#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/lib.h"

int main(int argc, char* argv[]) {
  // Convert ASCII STL file to binary
  char* fname;
  if (argc > 1) {
    fname = argv[1]; 
  } else {
    printf("Usage: stlp <filename> [-c=asc|bin | -i | -p <infill> <fprice> <wall-width> <material>]\n"
             "\t-c=asc|bin: convert to ASCII or binary STL\n"
             "\t-i: info about STL file (closed volume, number of vertices, surface area, number of triangles)\n"
             "\t-p <infill> <fprice>: calculates the price of an FDM 3D-printed model\n"
             "\t\t<infill>: amount of infill used by the printer in percentage (default is 20)\n"
             "\t\t<fprice>: price of 1 gramm of filament used to print the model in dollars (default is 0.08)\n"
             "\t\t<wall-width>: width of the outer, solid wall in millimeters (default is 1.2)\n"
             "\t\t<material>: type of materail used for printing, exactly one of:\n"
             "\t\t\tPLA, ABS, PETG, TPU, WOOD\n"
             "\tIf only <filename> is given as argument then it's the same as executing stlp <filename> -i\n");
    exit(0); 
  }
  if (strcmp(argv[1], "-c=asc") == 0) {
    // char* binarySTL = getFileContents(fname);
  } else if (strcmp(argv[1], "-c=bin") == 0) {
    //int isValid = validateSTLFile(argv[2], 'a');
  }

  printf("%d\n", validateSTLFile(fname, 'b'));

  return 0;
}
