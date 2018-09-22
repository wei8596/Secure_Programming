#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (1024)

int main(int argc, char* argv[]) {
  char* inBuf;
  char* outBuf;
  char* fmt = "the winner is: %s";

  inBuf = (char*) malloc(BUF_SIZE);
  if (inBuf == NULL) {
    return -1;
  }
  read(0, inBuf, BUF_SIZE);
  outBuf = (char*) malloc(BUF_SIZE);
  if (outBuf == NULL) {
    return -1;
  }
  sprintf(outBuf, fmt, inBuf);
  fprintf(stdout, "%s\n", outBuf);
  fprintf(stderr, "%s\n", outBuf);
  free(inBuf);
  free(outBuf);
}
