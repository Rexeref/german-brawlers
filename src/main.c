#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef __unix 
#include "linuxFunctions.h"
#elif _WIN32
#include "windowsFunctions.h"
#endif
#include "functions.h"

FILE *fatk;
FILE *fene;
FILE *save;

#ifdef _WIN32
#include <windows.h>
char listatk[40]=".vncprpg\\abilities.data";
char listene[40]=".vncprpg\\nemici.data";
char savename[40]=".vncprpg\\save.data";
#elif __unix
char listatk[40]=".vncprpg/abilities.data";
char listene[40]=".vncprpg/nemici.data";
char savename[40]=".vncprpg/save.data";
#endif

int main()
{
    #ifdef _WIN32
    int showFlag=0;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    #endif // _WIN32

    cleanS();
    
    
    /// Primo Avvio ///

    if(fopen(listatk, "r")==NULL || fopen(listene, "r")==NULL)
    {
        system("mkdir .vncprpg");
        fene=fopen(listene, "w");
        fatk=fopen(listatk, "w");
        fprintf(fatk, "Colpo Nullo\n0 0 0 1\nColpo\n1 0 0 1\nFiammella\n0 1 0 2\nLuce\n0 2 3 2\nLuce Concentrata\n0 2 1 2\nLuce Accecante\n0 3 3 2\nColpo d'arma\n2 0 1 1\nColpo d'arma caricato\n3 0 3 1\nColpo d'arma incantata\n2 2 6 3\nPalla di fuoco\n1 4 10 2\nInsegnamenti del maestro\n4 1 10 1\nEsplosione\n6 0 12 1\nEsplosione di Mana\n0 6 12 2\nCondivisione\n1 1 -12 0\nCura\n1 -2 12 0\nColpo caricato\n2 0 3 1");
        fprintf(fene, "Slime\n5 50    6 6 1 1    3 4 1   0 0    1 1 1 1 1 1\nGoblin delle Colline\n15 50    10 10 1 1    10 5 1   20 20    6 6 1 1 1 1\nScheletro\n30 50    13 13 15 15    20 10 1   50 200    0 0 7 6 1 1\nZombie\n50 50    19 19 1 1    33 26 8   0 100   1 1 1 1 1 1\nTroll\n70 100    25 25 64 64    35 26 1   75 100    6 6 7 7 0 0\nOccultista Iniziato\n85 50    31 31 26 50    42 15 15   75 75    14 14 14 13 6 4\nOccultista Guerriero\n100 50    51 51 16 16    55 36 1   150 0    6 6 7 7 15 15\nOccultista Stregone\n100 50    40 40 30 60    45 1 36   0 150    13 13 9 9 3 3\nOccultista Esperto\n120 50    70 70 26 50    60 25 25   90 110    14 14 13 13 6 4\n[31mViverna[0m\n120 200    2000 2000 3 180    60 40 1   190 50    13 13 11 11 14 14");
        fclose(fene);
        fclose(fatk);
    }


    /// Creazione del personaggio e recupero dei dati della partita precedente ///

    pg protagonista;
    srand(time(0));
    if(fopen(savename, "r")==NULL)
    {
        save=fopen(savename, "w");
        fclose(save);
        protagonista=resetPg(protagonista);
        printPgStats(protagonista);
        savenow(protagonista, savename);
    }
    else
    {
        protagonista=loadnow(protagonista, savename);
    }

    protagonista.p.x=LATOPOR/2-1;
    protagonista.p.y=LATOPVE-1;

    /// Menu' principale ///

    do
    {
        protagonista=menuavventura(protagonista, savename, listatk, listene);
    }
    while(protagonista.hp>0);

    protagonista = gameover(protagonista, savename);

    return 0;
}
