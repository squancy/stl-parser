#include <stdio.h>
#include <string.h>
#include "../src/headers/all.h"

int main(void) {
  int i;

  // Test input 
  char* fnames[] = {
    "../test/stl/long_ascii.stl",
    "../test/stl/long_ascii_v2.stl",
    "../test/stl/medium_ascii_v1.stl",
    "../test/stl/medium_ascii_v2.stl",
    "../test/stl/medium_ascii_v3.stl",
    "../test/stl/medium_ascii_v4.stl",
    "../test/stl/short_ascii_v1.stl",
    "../test/stl/short_ascii_v2.stl",
    "../test/stl/short_ascii_v3.stl",
    "../test/stl/short_ascii_v4.stl",
    "../test/stl/short_ascii_v6.stl",
    "../test/stl/wrong_ascii_v1.stl",
    "../test/stl/wrong_ascii_v2.stl",
    "../test/stl/wrong_ascii_v3.stl",
    "../test/stl/wrong_ascii_v4.stl",
    "../test/stl/wrong_ascii_v5.stl"
  };

  // Expected output
  int output[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
  };
  
  printf("Testing int validateSTLFile(char* fname, char type) in ASCII mode\n");
  for (i = 0; i < sizeof(output) / sizeof(output[0]); i++) {
    int res = validateSTLFile(fnames[i], 'a');
    char* status = res == output[i] ? "passed" : "failed";
    printf("input file: %s, output: %d --> %s\n", fnames[i], res, status);
  } 

  return 0;
}
