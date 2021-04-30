#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/lib.h"
#include "headers/stl.h"
#include "headers/const.h"
#include "headers/mat.h"

void printUsage(void);
int supportedMat(char* mat);

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
  } else if (flagExists("-i", argv, argc) || argc == 2) {
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
  } else if (flagExists("-p", argv, argc)) {
    int ind, i = 0;
    while (1) {
      if (strcmp(argv[i], "-p") == 0) {
        ind = i;
        break;
      } 
      i++;
    } 

    int isASCII = validateSTLFile(fname, 'a');
    int isBinary = validateSTLFile(fname, 'b');
    if (isASCII != 1 && isBinary != 1) {
      printf("ERROR: Invalid ASCII or binary STL file was given\n");
      exit(0);
    }

    float infill = ind + 1 < argc ? strtof(argv[ind + 1], NULL) / 100 : -1;
    float fprice = ind + 2 < argc ? strtof(argv[ind + 2], NULL) : -1;
    float wallWidth = ind + 3 < argc ? strtof(argv[ind + 3], NULL) / 10 : -1;
    char* material = ind + 4 < argc ? argv[ind + 4] : " ";

    // Make sure matrial is one that's supported
    if (!supportedMat(material) || infill == -1 || fprice == -1 || wallWidth == -1) {
      printf("ERROR: invalid or no parameter is given\n");
      exit(0);
    }

    char type = isASCII ? 'a' : 'b';
    float price = calcPrice(fname, type, infill, fprice, wallWidth, material);
    printf("Estimated price: $%.3f\n", price); 
  }

  return 0;
}

void printUsage(void) {
  printf("Usage: stlp <filename> [-c=asc|bin | -i | -p <infill> <fprice> <wall-width> <material>]\n"
           "\t-c=asc|bin: convert to ASCII or binary STL, output file is 'output.stl' created in the current directory\n"
           "\t-i: info about STL file (closed volume, number of vertices, surface area, number of triangles)\n"
           "\t-h: prints usage\n"
           "\t-p <infill> <fprice> <wall-width> <material>: calculates the price of an FDM 3D-printed model\n"
           "\t\t<infill>: amount of infill used by the printer in percentage\n"
           "\t\t<fprice>: price of 1 gramm of filament used to print the model in dollars\n"
           "\t\t<wall-width>: width of the outer, solid wall in millimeters\n"
           "\t\t<material>: type of materail used for printing, exactly one of:\n"
           "\t\t\tABS, PLA, CFRP, Plexiglass, Alumide, Aluminum, Brass, Bronze, Copper, Gold_14K, Gold_18K,\n"
           "\t\t\tPolyamide_MJF, Polyamide_SLS, Rubber, Silver, Steel, Titanium, Resin\n"
           "\tIf only <filename> is given as argument then it's the same as executing stlp <filename> -i\n");
}

int supportedMat(char* mat) {
  int i;
  for (i = 0; i < MAT_COUNT; i++) {
    if (strcmp(mat, MATERIALS[i]) == 0) {
      return 1;
    }
  }
  return 0;
} 
