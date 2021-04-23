#include <stdio.h>
#include <string.h>
#include "../src/headers/all.h"

int main(void) {
  int i;
  // Test input
  char* s1 = "hello world";
  char* s2 = "  hello world";
  char* s3 = "hello world     ";
  char* s4 = "hello    world";
  char* s5 = " hello   world    ";
  char* s6 = "  hello   world";
  char* s7 = "hello    world  ";

  // Expected output
  char* s1c = "hello world";
  char* s2c = "hello world";
  char* s3c = "hello world";
  char* s4c = "hello    world";
  char* s5c = "hello   world";
  char* s6c = "hello   world";
  char* s7c = "hello    world";

  char* sarr[7] = {s1, s2, s3, s4, s5, s6, s7};
  char* carr[7] = {s1c, s2c, s3c, s4c, s5c, s6c, s7c};

  printf("Testing char* strip(char* str)\n");
  for (i = 0; i < 7; i++) {
    char* status = strcmp(strip(sarr[i]), carr[i]) == 0 ? "passed" : "failed";
    printf("input: %s, output: %s --> %s\n", sarr[i], strip(sarr[i]), status);
  }

  printf("\n");

  // Expected output
  s1c = s2c = s3c = s4c = s5c = s6c = s7c = "hello world";
  char* carr2[7] = {s1c, s2c, s3c, s4c, s5c, s6c, s7c};
  
  printf("Testing char* strstrip(char* str)\n");
  for (i = 0; i < 7; i++) {
    char* status = strcmp(strstrip(sarr[i]), carr2[i]) == 0 ? "passed" : "failed";
    printf("input: %s, output: %s --> %s\n", sarr[i], strstrip(sarr[i]), status);
  }

  // Test input
  s1 = "aaa  bb ccc";
  s2 = "a b c";
  s3 = "  a b c";
  s4 = "x";

  // Expected output
  s1c = "aaa";
  s2c = "a";
  s3c = "";
  s4c = "x";

  char* sarr2[4] = {s1, s2, s3, s4};
  char* earr[4] = {s1c, s2c, s3c, s4c};
  
  printf("\n");
  printf("Testing char* firstSpace(char* str)\n");
  for (i = 0; i < 4; i++) {
    char* status = strcmp(firstSpace(sarr2[i]), earr[i]) == 0 ? "passed" : "failed";
    printf("input: %s, output: %s --> %s\n", sarr2[i], firstSpace(sarr2[i]), status);
  }

  // Test input
  s1 = "hello 0.0 is a sentence";
  s2 = "a 1 c";
  s3 = "a";

  int output[3] = {1, 0, 0};
  char* input[3] = {s1, s2, s3};

  printf("\n");
  printf("Testing int mwords(char* str)\n");
  for (i = 0; i < 3; i++) {
    char* status = mwords(input[i], 3) == output[i] ? "passed" : "failed";
    printf("input: %s, output: %d --> %s\n", input[i], mwords(input[i], 3), status);
  }

  // Test input
  char* x1 = "hello i like apples";
  char* x2 = "hello i like pears";
  char* x3 = "testing";
  char* x4 = "a b";
  char* x5 = "x";
  char* words[5];

  // Expected output
  char* x1s[5] = {"hello", "i", "like", "apples"};
  char* x2s[5] = {"hello", "i", "like", "pears"};
  char* x3s[1] = {"testing"};
  char* x4s[2] = {"a", "b"};
  char* x5s[1] = {"x"};

  printf("\n");
  printf("Testing void breakIntoWords(char* line, char* arr[])\n");
  breakIntoWords(x1, words);
  char* psd1 = (strcmp(words[0], x1s[0]) == 0 && strcmp(words[1], x1s[1]) == 0 &&
    strcmp(words[2], x1s[2]) == 0 && strcmp(words[3], x1s[3]) == 0 ? "passed" : "failed");
  printf("input: %s, output: [%s, %s, %s, %s] --> %s\n", x1, words[0], words[1], words[2], words[3], psd1);
  breakIntoWords(x2, words);
  char* psd2 = (strcmp(words[0], x2s[0]) == 0 && strcmp(words[1], x2s[1]) == 0 &&
    strcmp(words[2], x2s[2]) == 0 && strcmp(words[3], x2s[3]) == 0 ? "passed" : "failed");
  printf("input: %s, output: [%s, %s, %s, %s] --> %s\n", x2, words[0], words[1], words[2], words[3], psd2);
  breakIntoWords(x3, words);
  char* psd3 = strcmp(words[0], x3s[0]) == 0 ? "passed" : "failed";
  printf("input: %s, output: [%s] --> %s\n", x3, words[0], psd3);
  breakIntoWords(x4, words);
  char* psd4 = strcmp(words[0], x4s[0]) == 0 && strcmp(words[1], x4s[1]) == 0 ? "passed" : "failed";
  printf("input: %s, output: [%s, %s] --> %s\n", x4, words[0], words[1], psd4);
  breakIntoWords(x5, words);
  char* psd5 = strcmp(words[0], x5s[0]) == 0 ? "passed" : "failed";
  printf("input: %s, output: [%s] --> %s\n", x5, words[0], psd5);

  return 0;
}
