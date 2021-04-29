#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/lib.h"
#include "headers/stl.h"

void printUsage(void);

int main(int argc, char* argv[]) {
  // Convert ASCII STL file to binary
  char* fname;
  if (argc > 1) {
    int ind;
    if ((ind = getFilename(argv, argc)) > -1) {
      fname = argv[ind];
    } else if (flagExists("-h", argv, argc)) {
      printUsage();
      exit(0);
    }
  } else {
    printUsage();
    exit(0); 
  }

  if (flagExists("-c=asc", argv, argc)) {
    int valid = validateSTLFile(fname, 'b');
    if (valid == 0) {
      printf("ERROR: Invalid binary STL file given\n");
      exit(0);
    } else if (valid == 2) {
      printf("ERROR: File does not exists or invalid file was given\n");
      exit(0);
    }
    int state = convSTL(fname, 'a');
    if (state == 2) {
      printf("ERROR: Could not read binary STL file\n");
      exit(0);
    }
  } else if (flagExists("-c=bin", argv, argc)) {
    int valid = validateSTLFile(fname, 'a');
    if (valid == 0) {
      printf("ERROR: Invalid ASCII STL file given\n");
      exit(0);
    } else if (valid == 2) {
      printf("ERROR: File does not exists or invalid file was given\n");
      exit(0);
    }
    int state = convSTL(fname, 'b');
    if (state == 2) {
      printf("ERROR: Could not read binary STL file\n");
      exit(0);
    }
  } else if (flagExists("-i", argv, argc)) {
    int isASCII = validateSTLFile(fname, 'a');
    int isBinary = validateSTLFile(fname, 'b');
    if (isASCII != 1 && isBinary != 1) {
      printf("ERROR: Invalid ASCII or binary STL file was given\n");
      exit(0);
    }

    // File is either ASCII or binary, get information
    char type = isASCII ? 'a' : 'b';
    float params[4] = {0, 0, 0, 0};
    getSTLParams(fname, type, params);

    if (params[0] == 0 || params[1] == 0) {
      printf("ERROR: Could not read STL file\n");
    } else {
      printf("Information about %s\n", fname);
      printf("\tNumber of vertices: %.0f\n", params[0]);
      printf("\tNumber of facets: %.0f\n", params[1]);
      printf("\tVolume: %.3fcm^3\n", params[2]);
      printf("\tSurface area: %.3fcm^2\n", params[3]);
    }
  }

  return 0;
}

void printUsage(void) {
  printf("Usage: stlp <filename> [-c=asc|bin | -i | -p <infill> <fprice> <wall-width> <material>]\n"
           "\t-c=asc|bin: convert to ASCII or binary STL, output file is 'output.stl' created in the current directory\n"
           "\t-i: info about STL file (closed volume, number of vertices, surface area, number of triangles)\n"
           "\t-h: prints usage"
           "\t-p <infill> <fprice> <wall-width> <material>: calculates the price of an FDM 3D-printed model\n"
           "\t\t<infill>: amount of infill used by the printer in percentage (default is 20)\n"
           "\t\t<fprice>: price of 1 gramm of filament used to print the model in dollars (default is 0.08)\n"
           "\t\t<wall-width>: width of the outer, solid wall in millimeters (default is 1.2)\n"
           "\t\t<material>: type of materail used for printing, exactly one of:\n"
           "\t\t\tPLA, ABS, PETG, TPU, WOOD\n"
           "\tIf only <filename> is given as argument then it's the same as executing stlp <filename> -i\n");
}
