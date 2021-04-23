#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAXCHAR 1000

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

// Checks if character is alphanumeric
int isan(char c) {
  return isalpha(c) || isdigit(c);
}

// Returns true if there are more than n words in a string (separated by a space)
int mwords(char* str, int n) {
  int i = 0, words = 0;
  while (str[i] != '\0') {
    if ((i == 0 && str[i + 1] == ' ') || (i > 0 && isan(str[i - 1]) && str[i] == ' ' && isan(str[i + 1]))) {
      words++;
    }
    i++;
  }
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

// Syntactically check the validity of an STL file
int validateSTLFile(char* fname, char type) {
  if (type == 'a') {
    // Validate ASCII STL
    /*
      solid [name]
        facet normal v1 v2 v3
          outer loop
            vertex  v1x v1y v1z
            vertex  v2x v2y v2z
            vertex  v3x v3y v3z
          endloop
        endfacet  
        {...}
      endsolid
    */
    FILE *fp = fopen(fname, "r"); 
    char buf[MAXCHAR];
    int i = 0;

    // Make sure first line starts with "solid" and there's an optional name after that
    // Last line must be "endsolid" with some potentially empty lines after that
    char* firstLine = strstrip(fgets(buf, MAXCHAR, fp));
    int moreWords = mwords(firstLine, 2);
    if (strcmp(firstSpace(firstLine), "solid") != 0 || moreWords) {
      return 0;
    }
    
    int j, isEnd = 0;
    while (1) {
      while (i < 7) {
        char* l = fgets(buf, MAXCHAR, fp);
        if (l == NULL) {
          return 0;
        }

        char* nextLine = strstrip(l);

        if (strlen(nextLine) == 0) {
          continue;
        }

        if (strcmp(nextLine, "endsolid") == 0) {
          // No content can be after "endsolid" keyword
          while (1) {
            char* l = fgets(buf, MAXCHAR, fp);
            if (l == NULL) {
              return 1;
            }
            char* nl = strstrip(l);
            if (strlen(nl) != 0) {
              return 0;
            }
          }
        }
        
        // Validate facet [...] endfacet section
        if ((i == 0 && mwords(nextLine, 5)) ||
           (i == 1 && mwords(nextLine, 2)) ||
           ((i == 2 || i == 3 || i == 4) && mwords(nextLine, 4)) ||
           ((i == 5 || i == 6) && mwords(nextLine, 1))) {
          return 0;
        }
        
        char* words[5];
        breakIntoWords(nextLine, words);
        if (i == 0) {
          int keywordCheck = strcmp(words[0], "facet") == 0 && strcmp(words[1], "normal") == 0;
          if (!keywordCheck || !validateCoords(words[2], words[3], words[4])) {
            return 0;
          }
        } else if (i == 1 && (strcmp(words[0], "outer") != 0 || strcmp(words[1], "loop") != 0)) {
          return 0;
        } else if (i == 2 || i == 3 || i == 4) {
          int keywordCheck = strcmp(words[0], "vertex") == 0;
           if (!keywordCheck || !validateCoords(words[1], words[2], words[3])) {
            return 0;
          }          
        } else if (i == 5 && strcmp(words[0], "endloop") != 0) {
          return 0; 
        } else if (i == 6 && strcmp(words[0], "endfacet") != 0) {
          return 0;
        }
        i++;
      } 
      i = 0;
    }
  } else {
    // Validate binary STL
  }
  return 0;
}
