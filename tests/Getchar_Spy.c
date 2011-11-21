#include <stdio.h>
#include <string.h>

#include "Getchar_Spy.h"

#define MAX 1000

char buffer[MAX];
int ep = 0;

void getchar_expect(const char* expect) {
  strncpy(buffer, expect, MAX);
  buffer[MAX-1] = '\0';
  ep = 0;
}

int getchar_next(void) {
  if (ep==MAX) return EOF;
  if (buffer[ep] == '\0') return EOF;
  return buffer[ep++];
}
