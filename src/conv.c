#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headers/all.h"
#include "headers/stl.h"
#include "headers/const.h"

#define FL_LEN 100

int convSTL(char* fname, char type) {
  FILE* rfp = fopen("./output.stl", "wb+");
  FILE* fp;
  if (type == 'a') {
    // Input is binary, convert to ASCII
    int k = 0;
    unsigned char header[80];
    fp = fopen(fname, "rb");
    if (fp == NULL) {
      fclose(fp);
      return 2;
    }

    unsigned int numOfTriangles;
    fread(header, HEADER_BYTES, 1, fp);
    fread(&numOfTriangles, COORD_BYTES , 1, fp);
    fprintf(rfp, "solid\n");

    int i, j;
    for (i = 0; i < numOfTriangles; i++) {
      fprintf(rfp, "facet normal ");
      for (j = 0; j < 13; j++) {
        if (j % 12 == 0 && j != 0) {
          // Attribute field is ignored since it's not represented in ASCII
          unsigned int attr;
          fread(&attr, ATTR_BYTES, 1, fp);
        } else {
          if (j < 3) {
            float v;
            fread(&v, sizeof(float), 1, fp);
            if (j == 2) {
              fprintf(rfp, "%e\n", v);
            } else {
              fprintf(rfp, "%e ", v);
            }
          } else {
            if (j == 3) {
              fprintf(rfp, "outer loop\n");
            }
            if (j >= 3) {
              if (j % 3 == 0) {
                fprintf(rfp, "vertex ");
              }
              float v;
              fread(&v, sizeof(float), 1, fp);
              if (j % 3 == 2) {
                fprintf(rfp, "%e\n", v);
              } else {
                fprintf(rfp, "%e ", v);
              }
            }
          }
        }
      }
      fprintf(rfp, "endloop\nendfacet\n");
      k++;
    }
    fprintf(rfp, "endsolid");
  } else {
    // Input is ASCII, convert to binary
    int i;
    fp = fopen(fname, "r"); 
    if (fp == NULL) {
      fclose(fp);
      return 2;
    }
    
    // Header if full of 0s
    unsigned char header[HEADER_BYTES];
    for (i = 0; i < HEADER_BYTES; i++) {
      header[i] = ' ';
    }
    
    fwrite(header, sizeof(unsigned char), HEADER_BYTES, rfp);
  
    // Get number of triangles
    float params[4] = {0, 0, 0, 0};
    getSTLParams(fname, 'a', params);
    unsigned int numOfTriangles = params[1];
    fwrite(&numOfTriangles, COORD_BYTES, 1, rfp);

    char buf[MAXCHAR];
    int cnt = 0;
    while (1) {
      char* l = fgets(buf, MAXCHAR, fp);
      if (l == NULL) {
        fclose(fp);
        break;
      }

      char* nl = strstrip(l);      
      char* words[5];
      breakIntoWords(nl, words);
      if (strstartsw(nl, "facet") || strstartsw(nl, "vertex")) {
        int sind = strstartsw(nl, "facet") ? 2 : 1;
        cnt++;
        float vs[3];   
        vs[0] = strtof(words[sind], NULL);
        vs[1] = strtof(words[sind + 1], NULL);
        vs[2] = strtof(words[sind + 2], NULL);
        fwrite(&vs, sizeof(float), 3, rfp);
        if (cnt == 4) {
          int attrs[2] = {0, 0};
          fwrite(&attrs, 1, ATTR_BYTES, rfp);
          cnt = 0;
        }
      }
    }
  }

  fclose(rfp);
  fclose(fp);
  return 1;
}
