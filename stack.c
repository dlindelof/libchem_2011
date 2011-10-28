#include <stdio.h>

#include "stack.h"

#define MAXVAL 100

int sp = 0;
float val[MAXVAL];

void push(float f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

float pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
