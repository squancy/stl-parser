#include <stdio.h>
#include <string.h>
#include "headers/all.h"
#include "headers/const.h"

// Return number of vertices & triangles, volume, surface area
void getSTLParams(char* fname, char type, int params[4]) {
  if (type == 'a') {
    FILE* fp = fopen(fname, "r"); 
    char buf[MAXCHAR];
    if (fp == NULL) {
      fclose(fp);
      return;
    }
    
    while (1) {
      char* l = fgets(buf, MAXCHAR, fp);
      if (l == NULL) {
        fclose(fp);
        break;
      }

      char* nextLine = strstrip(l);

      if (strlen(nextLine) == 0) {
        continue;
      }

      if (strstartsw(nextLine, "vertex")) {
        params[0]++; 
      } else if (strstartsw(nextLine, "facet")) {
        params[1]++;     
      }
    }
  } else {

  }
}
