#ifndef LIB_H
#define LIB_H

int validateSTLFile(char* fname, char type);
int flagExists(char* flag, char* args[], int size);
int getFilename(char* args[], int size);
int convSTL(char* fname, char type);
float calcPrice(char* fname, char type, float infill, float fprice, float wallWidth, char* material);

#endif
