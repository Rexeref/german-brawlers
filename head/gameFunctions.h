#ifndef GAMEFUNCTIONS_H_INCLUDED
#define GAMEFUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LATOPOR 15
#define LATOPVE 10

#include "structs.h"

///
/// DICHIARIAZIONE DELLE FUNZIONI
///

// Funzioni Generali
void savenow(pg personaggio, char nomefile[]);
pg loadnow(pg personaggio, char nomefile[]);
pg gameover(pg personaggio, char savefile[]);
pg resetPg(pg personaggio);
pg newlevel(pg personaggio);
pg newResistanceLevel(pg personaggio);
void printPgStats(pg personaggio);
pg menuavventura(pg personaggio, char salvataggio[], char fileattacco[], char filenemici[]);
pg menudebug(pg personaggio, char salvataggio[], char fileattacco[], char filenemici[]);

// Fight System
pg fight(pg personaggio, char fileattacco[], char filenemici[]);
pg enemyAttack(pg personaggio, enem* nemico, char fileattacco[]);
void printEnemy(enem personaggio);
enem loadEnemy(int indexEnemyInList, char nomefile[]);
attack prendidatiattacco(int numero, char fileattacco[]);
pg newability(pg personaggio, char fileattacco[]);
int getFileLinesNumber(char nomefile[]);
void printAbility(attack attacco);
void mostraattacchi(pg personaggio, char fileattacco[]);

// Expl
pg esplorazione(pg personaggio, char salvataggio[], char fileattacco[], char filenemici[]);
void printMatrice(int matrice[LATOPVE][LATOPOR]);

// Funzioni Utilita' Portabili
int ifWRound(double number);
void printSchermataBarreVita(pg personaggio, enem nemico);

#ifdef _WIN32
#include "windows/windowsFunctions.h"
#elif __linux__
#include "linux/linuxFunctions.h"
#endif

#endif
