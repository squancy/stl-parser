#ifndef ALL_H
#define ALL_H

int validateSTLFile(char* fname, char type);
char* strstrip(char* str);
char* strip(char* str);
char* firstSpace(char* str);
int mwords(char* str, int n);
void breakIntoWords(char* line, char* arr[]);
int validateCoords(char* s1, char* s2, char* s3);
int strstartsw(char* str, char* substr);
int flagExists(char* flag, char* args[], int size);
int getFilename(char* args[], int size);

#endif
