#ifndef LIB_H
#define LIB_H

int validateSTLFile(char* fname, char type);
char* strstrip(char* str);
char* strip(char* str);
char* firstSpace(char* str);
int mwords(char* str, int n);
void breakIntoWords(char* line, char* arr[]);
int validateCoords(char* s1, char* s2, char* s3);

#endif
