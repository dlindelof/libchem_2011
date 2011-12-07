#include <stdio.h>
#include <stdlib.h>

#include "chem.h"
#include "getop.h"
#include "stack.h"

int main() {
  int type;
  float op2, op1;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      push(chem_fmod(pop(), op2));
      break;
    case SQRT:
      push(chem_sqrt(pop()));
      break;
    case CBRT:
      push(chem_cbrt(pop()));
      break;
    case SMALL_ROOT:
      op1 = pop();
      op2 = pop();
      push(chem_smallest_root(pop(), op2, op1));
      break;
    case GCD:
      op1 = pop();
      push(chem_gcd(pop(), op1));
      break;
    case SINE:
      push(chem_sin(pop()));
      break;
    case '?':
      printf("\t%.8g\n", peek());
      break;
    case 'w':
      op2 = pop();
      op1 = pop();
      push(op2);
      push(op1);
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}
