#include <stdio.h>
#include <string.h>
#include "../src/headers/all.h"
#include "../src/headers/colors.h"

int main(void) {
  int i;
  char* args[] = {
    ".",
    "-c=asc",
    "hello",
    "invalid",
    "xx",
    "abc def",
    "   "
  }; 

  char* pargs[] = {
    "-p",
    "-c=asc",
    "-c=bin",
    "invalid",
    "yy",
    "abcdef",
    " "
  };

  int expected[] = {
    0, 1, 0, 1, 0, 0, 0
  };

  int size = sizeof(expected) / sizeof(expected[0]);

  for (i = 0; i < sizeof(args) / sizeof(args[0]); i++) {
    int res = flagExists(pargs[i], args, size);
    char* status = res == expected[i] ? "passed" : "failed";
    if (strcmp(status, "passed") == 0) {
      printf(GREEN "input: %s, output: %d --> %s\n" RESET, args[i], res, status);
    } else {
      printf(RED "input: %s, output: %d --> %s\n" RESET, args[i], res, status);
    }
  }

  return 0;
}
