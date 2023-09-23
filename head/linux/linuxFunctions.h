#ifndef LINUXFUNCTIONS_H_INCLUDED
#define LINUXFUNCTIONS_H_INCLUDED

#include "../functions.h"

enem menudegiocatore(pg* personaggio, enem nemico, char fileattacco[]);
void cleanS(void);
void stop(void);
void pause(void);
void printaBarra(float valore, float max, char color);
int kbhit();

#endif