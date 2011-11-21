#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "getop.h"
#include "getch.h"

int getop(char s[]) {
	int i,c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i=0;
	if (!isalpha(c) && !isdigit(c) && c != '.' && c != '-')
		return c;
        if (isalpha(c)) {
          while(isalpha(s[++i] = c = getch()))
            ;
          s[i] = '\0';
          if (c != EOF)
            ungetch(c);
          if (!strcmp(s, "sqrt"))
            return SQRT;
          else
            return ERROR;
        }
	if (c=='-' && !isdigit(s[++i]=c=getch())) {
	  ungetch(c);
	  return '-';
	}
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
