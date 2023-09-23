#ifndef WINDOWSFUNCTIONS_H_INCLUDED
#define WINDOWSFUNCTIONS_H_INCLUDED

#include "gameFunctions.h"

enem menudegiocatore(pg *appoggio, enem nemico, char fileattacco[]);
void cleanS(void);
void stop(void);
void pause(void);
void printaBarra(float valore, float max, char color);

#endif