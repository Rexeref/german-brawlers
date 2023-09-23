#ifndef GAMEFUNCTIONS_H_INCLUDED
#define GAMEFUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#ifdef _WIN32
#include "windows/windowsFunctions.h"
#elif __linux__
#include "linux/linuxFunctions.h"
#endif

#define LATOPOR 15
#define LATOPVE 10

///
/// STRUCT
///

typedef struct{
    int x;
    int y;
    int e;
} coordinate;

typedef struct{
    char name[255];
    ///Dati combattimento
    int hp; //Punti vita attuali
    int sp; //Punti abilit� attuali
    ///Stats
    int lvl; //Livello, ogni livello ti permetti di aumentare di 1 una statistica a propria scelta
    int exp; //Ogni 1000 XP si sale di 1 livello
    int rexp; //Punti esperienza per le resistenze
    int mhp; //Vita massima
    int msp; //Punti abilit� massimi (mana)
    int spd; //Chi ha questa statistica pi� alta combatte per primo, ogni 10 livelli si aggiunge un attacco in pi�
    int pow; //Permette di fare pi� danni fisici, ogni 2 livelli si pu� usare un'arma che pesa 1 punto peso in pi� (I punti peso standard sono 30)
    int mind; //Permette di fare pi� danni magici, ogni 5 livelli il costo in SP di una magia diminuisce di 1
    ///Altro
    int abilities[6]; //Indicatori di quali abilit� sono accessibili, i dati sono salvati in un file
    int weapon;
    int posizione;
    int healingKits;
    coordinate p;
    int deaths;

    float powRes;
    float mindRes;
} pg;

typedef struct{
    char name[255];
    ///Dati combattimento
    int hp; //Punti vita attuali
    int sp; //Punti abilit� attuali
    ///Stats
    int lvl; //Livello, ogni livello ti permetti di aumentare di 1 una statistica a propria scelta
    int exp; //Ogni 1000 XP si sale di 1 livello
    int mhp; //Vita massima
    int msp; //Punti abilit� massimi (mana)
    int spd; //Chi ha questa statistica pi� alta combatte per primo, ogni 10 livelli si aggiunge un attacco in pi�
    int pow; //Permette di fare pi� danni fisici, ogni 2 livelli si pu� usare un'arma che pesa 1 punto peso in pi� (I punti peso standard sono 30)
    int mind; //Permette di fare pi� danni magici, ogni 5 livelli il costo in SP di una magia diminuisce di 1
    ///Altro
    int abilities[6]; //Indicatori di quali abilit� sono accessibili, i dati sono salvati in un file
    float powRes;
    float mindRes;
} enem;

typedef struct{
    char name[255];
    float multdamagepow;
    float multdamagemind;
    int spCost;
    int target;
} attack;

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

#endif
