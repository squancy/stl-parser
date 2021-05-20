#include <stdio.h>
#include <string.h>
#include "../src/headers/all.h"
#include "../src/headers/colors.h"

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
    "../test/stl/wrong_ascii_v5.stl",
    "../test/stl/this_ascii_does_not_exist.stl"
  };

  // Expected output
  int output[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2
  };
  
  printf("Testing int validateSTLFile(char* fname, char type) in ASCII mode\n");
  for (i = 0; i < sizeof(output) / sizeof(output[0]); i++) {
    int res = validateSTLFile(fnames[i], 'a');
    char* status = res == output[i] ? "passed" : "failed";
    if (strcmp(status, "passed") == 0) {
      printf(GREEN "input file: %s, output: %d --> %s\n" RESET, fnames[i], res, status);
    } else {
      printf(RED "input file: %s, output: %d --> %s\n" RESET, fnames[i], res, status);
    }
  } 

  char* fnames2[] = {
    "../test/stl/binary_v1.stl",
    "../test/stl/binary_v2.stl",
    "../test/stl/binary_v3.stl",
    "../test/stl/binary_v4.stl",
    "../test/stl/binary_v5.stl",
    "../test/stl/binary_v6.stl",
    "../test/stl/binary_v7.stl",
    "../test/stl/binary_wrong_v1.stl",
    "../test/stl/binary_wrong_v2.stl",
    "../test/stl/binary_wrong_v3.stl",
    "../test/stl/this_binary_does_not_exist.stl"
  };

  int output2[] = {
    1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2
  };

  printf("\n");
  printf("Testing int validateSTLFile(char* fname, char type) in binary mode\n");
  for (i = 0; i < sizeof(output2) / sizeof(output2[0]); i++) {
    int res = validateSTLFile(fnames2[i], 'b');
    char* status = res == output2[i] ? "passed" : "failed";
    if (strcmp(status, "passed") == 0) {
      printf(GREEN "input file: %s, output: %d --> %s\n" RESET, fnames2[i], res, status);
    } else {
      printf(RED "input file: %s, output: %d --> %s\n" RESET, fnames2[i], res, status);
    }
  }

  return 0;
}
