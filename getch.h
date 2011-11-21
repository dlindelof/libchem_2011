#ifndef GETCH_H_
#define GETCH_H_

extern int (*calc_getchar)(void);

int getch(void);
void ungetch(int);


#endif /* GETCH_H_ */
