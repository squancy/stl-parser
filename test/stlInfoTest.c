#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../src/headers/all.h"
#include "../src/headers/stl.h"

#define EPSILON 0.1

int main(void) {
  int i, j;
  float params[4] = {0, 0, 0, 0};

  // Test input
  char* fnames[] = {
    "../test/stl/binary_v1.stl",
    "../test/stl/binary_v2.stl",
    "../test/stl/binary_v3.stl",
    "../test/stl/binary_v4.stl",
    "../test/stl/binary_v5.stl",
    "../test/stl/binary_v6.stl",
    "../test/stl/binary_v7.stl",
    "../test/stl/long_ascii_v2.stl"
  };

  char types[] = {
    'b', 'b', 'b', 'b', 'b', 'b', 'b', 'a'
  };

  // Expected output
  float output[][4] = {
    {36, 12, 0.001, 0.06},
    {114426, 38142, 1440.543, 987.738},
    {11208, 3736, 124.298, 457.374},
    {11196, 3732, 124.296, 457.385},
    {45840, 15280, 30.047, 76.372},
    {8796, 2932, 18.487, 373.057},
    {7044, 2348, 12.503, 223.441},
    {114426, 38142, 1440.543, 987.738}
  };

  for (i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
    getSTLParams(fnames[i], types[i], params); 
    int fl = 1;
    for (j = 0; j < 4; j++) {
      if (fabs(params[j] - output[i][j]) > EPSILON) {
        fl = 0;
        break;
      } 
    }

    char* status = fl ? "passed" : "failed";
    printf("input: %s, %c, [0, 0, 0, 0], output: %.0f, %.0f, %.3f, %.3f --> %s\n", fnames[i], types[i],
      params[0], params[1], params[2], params[3], status);

    for (j = 0; j < 4; j++) {
      params[j] = 0;
    }
  }

  return 0;
}
