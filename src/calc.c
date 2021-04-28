#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headers/all.h"
#include "headers/const.h"

// Get the volume of the model by summing the volumes of signed tetrahedrons
// Staring from index 0 every 3 coordniates make a triangle
float volume(float vertices[], int size) {
  int i;
  float vol = 0;
  for (i = 0; i < size; i++) {
    if ((i + 1) % 9 == 0) {
      // Area of a single signed tetrahedron
      float v321 = vertices[i - 8] * vertices[i - 4] * vertices[i];
      float v231 = vertices[i - 5] * vertices[i - 7] * vertices[i];
      float v312 = vertices[i - 8] * vertices[i - 1] * vertices[i - 3];
      float v132 = vertices[i - 2] * vertices[i - 7] * vertices[i - 3];
      float v213 = vertices[i - 5] * vertices[i - 1] * vertices[i - 6];
      float v123 = vertices[i - 2] * vertices[i - 4] * vertices[i - 6];
      vol += (1.0 / 6.0) * (-v321 + v231 + v312 - v132 - v213 + v123);
    }
  }
  return fabs(vol) / 1000;
}

// Get the surface area of the mesh by summing the areas of all the triangles
float surfArea(float vertices[], int size) {
  int i;
  float area = 0;
  for (i = 0; i < size; i++) {
    if ((i + 1) % 9 == 0) {
      float ax = vertices[i - 5] - vertices[i - 2];
      float ay = vertices[i - 4] - vertices[i - 1];
      float az = vertices[i - 3] - vertices[i];
      float bx = vertices[i - 8] - vertices[i - 2];
      float by = vertices[i - 7] - vertices[i - 1];
      float bz = vertices[i - 6] - vertices[i];
      float cx = ay * bz - az * by;
      float cy = az * bx - ax * bz;
      float cz = ax * by - ay * bx;
      area += 0.5 * sqrt(cx * cx + cy * cy + cz * cz);
    }
  }
  return area / 100;
}

// Return number of vertices & triangles, volume, surface area
void getSTLParams(char* fname, char type, float params[4]) {
  float* vertices = malloc(sizeof(float) * 3);
  int k = 0;
  if (type == 'a') {
    // ASCII STL
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
        vertices = realloc(vertices, sizeof(float) * (k + 3));
        params[0]++; 
        char* words[4];
        breakIntoWords(nextLine, words);
        for (int i = 1; i < 4; i++) {
          vertices[k++] = strtof(words[i], NULL);
        }
      } else if (strstartsw(nextLine, "facet")) {
        params[1]++;
      }
    }

    float v = volume(vertices, k);
    params[2] = volume(vertices, k);
    params[3] = surfArea(vertices, k);
    free(vertices);
  } else {
    // Binary STL
    unsigned char header[80];
    FILE* fp = fopen(fname, "rb");
    if (fp == NULL) {
      fclose(fp);
      return;
    }
    
    // Read header & num of triangles
    unsigned int numOfTriangles;
    fread(header, HEADER_BYTES, 1, fp);
    fread(&numOfTriangles, COORD_BYTES , 1, fp);
    params[1] = numOfTriangles;
    
    int i, j;
    for (i = 0; i < numOfTriangles; i++) {
      for (j = 0; j < 13; j++) {
        if (j % 12 == 0 && j != 0) {
          unsigned int attr;
          fread(&attr, ATTR_BYTES, 1, fp);
        } else {
          if (j < 3) {
            float tmp;
            fread(&tmp, sizeof(float), 1, fp);
            continue;
          }
          vertices = realloc(vertices, sizeof(float) * (k + 3));
          fread(&vertices[k++], sizeof(float), 1, fp);
          params[0]++;
        }
      }
    }
    float a = volume(vertices, k);
    float b = surfArea(vertices, k);
    params[2] = volume(vertices, k);
    params[3] = surfArea(vertices, k);
    printf("vol: %f, area: %f\n", a, b);
  }
}
