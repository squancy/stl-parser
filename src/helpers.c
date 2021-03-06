#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "headers/const.h"

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

// Replace every sequence of one or more whitespaces with a single space
char* strstrip(char* s) {
  unsigned int size = strlen(s);
  char* str = malloc(sizeof(char) * size + 1);
  strcpy(str, s);
  str = strip(str);
  char* res = malloc(sizeof(char) * size + 1);
  int k = 0;
  for (int i = 0; i < size; i++) {
    if (isWhitespace(str[i])) {
      for (int j = i + 1; j < size; j++) {
        if (isWhitespace(str[j])) {
          i++;
        } else {
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

// String before the first space
char* firstSpace(char* str) {
  char* res = malloc(sizeof(char) * strlen(str) + 1);
  int i = 0, k = 0;
  while (str[i] != '\0') {
    if (str[i] == ' ') {
      res[i] = '\0'; 
      break;
    } else {
      res[k++] = str[i];
    }
    i++;
  }
  res[k] = '\0';
  return res;
}

// Checks if character is alphanumeric or '+' or '.'
int isan(char c) {
  return isalpha(c) || isdigit(c) || c == '+' || c == '.' || c == '-';
}

// Returns true if there are more than n words in a string (separated by a space)
int mwords(char* str, int n) {
  int i = 0, words = 0;
  while (str[i] != '\0') {
    if (str[i] == ' ') {
      words++;
    }
    i++;
  }
  words++;
  return words > n ;
}

// Break a string of words into an array of words
void breakIntoWords(char* line, char* arr[]) {
  int l = 0, k = 0, i = 0, flag = 0; 
  while (line[i] != '\0')  {
    if (isan(line[i]) && !flag) {
      l = i;
      flag = 1;
    }

    if (line[i] == ' ' || line[i + 1] == '\0') {
      char* buf = malloc(sizeof(char) * 100);
      int amount = line[i + 1] == '\0' ? i - l + 1 : i - l;
      strncpy(buf, (line + l), amount);
      arr[k++] = buf;
      flag = 0;
    }
    i++;
  }
}

// Validate x, y, z coords
int validateCoords(char* s1, char* s2, char* s3) {
  char* n1, *n2, *n3;
  float x = strtof(s1, &n1);
  float y = strtof(s2, &n2);
  float z = strtof(s3, &n3);
  return !(*n1 != '\0' || *n2 != '\0' || *n3 != '\0');
}

// Checks whether string starts with a given substring
int strstartsw(char* str, char* substr) {
  int i = 0;
  while (substr[i] != '\0') {
    if (str[i] != substr[i]) {
      return 0;
    }
    i++;
  }
  return 1;
}

// Syntactically check the validity of an STL file
// Returns 0 if the file is syntactially invalid, 1 if correct, 2 if error while reading the file
int validateSTLFile(char* fname, char type) {
  if (type == 'a') {
    // Validate ASCII STL
    /*
      solid [name]
        facet normal v1 v2 v3
          outer loop
            vertex v1x v1y v1z
            vertex v2x v2y v2z
            vertex v3x v3y v3z
          endloop
        endfacet  
        {...}
      endsolid
    */
    FILE *fp = fopen(fname, "r"); 
    if (fp == NULL) {
      fclose(fp);
      return 2;
    }
    char buf[MAXCHAR];
    int i = 0;

    // Make sure first line starts with "solid" and there's an optional name after that
    // Last line must be "endsolid" with some potentially empty lines after that
    char* firstLine = strstrip(fgets(buf, MAXCHAR, fp));
    int moreWords = mwords(firstLine, 2);
    char* comp = firstSpace(firstLine);
    if (strcmp(comp, "solid") != 0 || moreWords) {
      fclose(fp);
      return 0;
    }

    free(firstLine);
    free(comp);
    
    int j, isEnd = 0;
    while (1) {
      while (i < 7) {
        char* l = fgets(buf, MAXCHAR, fp);
        if (l == NULL) {
          fclose(fp);
          return 0;
        }

        char* nextLine = strstrip(l);

        if (strlen(nextLine) == 0) {
          continue;
        }

        if (strstartsw(nextLine, "endsolid") && !mwords(nextLine, 2)) {
          // No content can be after "endsolid" keyword
          while (1) {
            char* l = fgets(buf, MAXCHAR, fp);
            if (l == NULL) {
              fclose(fp);
              return 1;
            }
            char* nl = strstrip(l);
            if (strlen(nl) != 0) {
              fclose(fp);
              return 0;
            }
            free(nl);
          }
        }
        
        // Validate facet [...] endfacet section
        if ((i == 0 && mwords(nextLine, 5)) ||
           (i == 1 && mwords(nextLine, 2)) ||
           ((i == 2 || i == 3 || i == 4) && mwords(nextLine, 4)) ||
           ((i == 5 || i == 6) && mwords(nextLine, 1))) {
          fclose(fp);
          return 0;
        }
        
        char* words[5];
        breakIntoWords(nextLine, words);
        if (i == 0) {
          int keywordCheck = strcmp(words[0], "facet") == 0 && strcmp(words[1], "normal") == 0;
          if (!keywordCheck || !validateCoords(words[2], words[3], words[4])) {
            fclose(fp);
            return 0;
          }
        } else if (i == 1 && (strcmp(words[0], "outer") != 0 || strcmp(words[1], "loop") != 0)) {
          fclose(fp);
          return 0;
        } else if (i == 2 || i == 3 || i == 4) {
          int keywordCheck = strcmp(words[0], "vertex") == 0;
           if (!keywordCheck || !validateCoords(words[1], words[2], words[3])) {
            fclose(fp);
            return 0;
          }          
        } else if (i == 5 && strcmp(words[0], "endloop") != 0) {
          fclose(fp);
          return 0; 
        } else if (i == 6 && strcmp(words[0], "endfacet") != 0) {
          fclose(fp);
          return 0;
        }
        i++;
      } 
      i = 0;
    }
  } else {
    // Validate binary STL
    /*
      UInt8[80] - header
      Uint32 - num of triangles
      Real32[3] - normal vector coords
      Real32[3] - v1 x, y, z
      Real32[3] - v2 x, y, z
      Real32[3] - v3 x, y, z
      Uint16[16] - attr byte count (mostly zero, now it's ignored)
    */
   
    // Header does not contain relevant info but save it anyways
    /*
      Note: according to the specs header must not begin with the keyword "solid" in order to
      be easily distinguishable from ASCII files
      however, this is almost always false and should not be relied on
    */
    unsigned int i, j;
    unsigned char header[HEADER_BYTES];
    FILE* fp = fopen(fname, "rb");
    if (fp == NULL) {
      fclose(fp);
      return 2;
    }
    
    // Read header & num of triangles
    unsigned int numOfTriangles;
    if (fread(header, HEADER_BYTES, 1, fp) != 1 || fread(&numOfTriangles, COORD_BYTES , 1, fp) != 1) {
      fclose(fp);
      return 2;
    }

    // Validate vertices and normal vector coords
    for (i = 0; i < numOfTriangles; i++) {
      for (j = 0; j < 13; j++) {
        // After a block of 16 floats there is a 2 byte unsigned int
        // It may contain color information but that's non-standard and ignored for now
        if (j % 12 == 0 && j != 0) {
          unsigned int attr;
          if (fread(&attr, ATTR_BYTES, 1, fp) != 1) {
            fclose(fp);
            return 2;
          }
        } else {
          float v;
          if (fread(&v, sizeof(float), 1, fp) != 1) {
            fclose(fp);
            return 2;
          }
        }
      }
    }
    return 1;
  }
  return 0;
}

// Check if a given flag exists in argv[]
int flagExists(char* flag, char* args[], int size) {
  int i; 
  for (i = 1; i < size; i++) {
    if (strcmp(args[i], flag) == 0) {
      return 1;
    }
  }
  return 0;
}

// Returns the index of filename found in in argv[]
// If it was not found it returns -1
int getFilename(char* args[], int size) {
  int i;
  FILE* fp;
  for (i = 1; i < size; i++) {
    if ((fp = fopen(args[i], "r")) != NULL) {
      fclose(fp);
      return i;
    } else {
      fclose(fp);
    }
  }
  return -1;
}
