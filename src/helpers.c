#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int isWhitespace(char c) {
  return c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v' || c == '\n';
}

// Remove whitspace from both ends
char* strip(char* str) {
  unsigned int size = strlen(str);
  char* res = malloc(sizeof(char) * size + 1);
  int fc = -1, lc = -1, i = 0, k = 0;
  while (str[i] != '\0') {
    if (!isWhitespace(str[i]) && fc == -1) {
      fc = i;
    }
    if (!isWhitespace(str[i])) {
      lc = i;
    }
    i++;
  }

  for (i = fc; i <= lc; i++) {
    res[k++] = str[i];
  }
  res[k] = '\0';
  return res;
}

// Replace every other whitespace with a space
char* strstrip(char* s) {
  unsigned int size = strlen(s);
  char* str = malloc(sizeof(char) * size + 1);
  strcpy(str, s);
  char* res = malloc(sizeof(char) * size + 1);
  int k = 0;
  for (int i = 0; i < size; i++) {
    if (isWhitespace(str[i])) {
      for (int j = i + 1; j < size; j++) {
        if (isWhitespace(str[j])) {
        } else {
          i++;
          break;
        }
      }
    }
    res[k++] = str[i];
  }
  res[k] = '\0';
  free(str);
  return res;
}

// Syntactically check the validity of an STL file
int validateSTLFile(char* fname, char type) {
  if (type == 'a') {
    // Validate ASCII STL
    FILE *fp = fopen(fname, "r"); 
    char buf[1000];
    int i = 0;
    while (fgets(buf, 1000, fp) != EOF) {
    
    }
  } else {
    // Validate binary STL
  }
  return 0;
}
