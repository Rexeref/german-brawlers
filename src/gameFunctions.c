#include "gameFunctions.h"

#ifdef __linux__
#include "linux/linuxFunctions.h"

#define CLEARSCREEN system("clear")
#define CHECKKEY
#define NBGETCHAR

#define kbh() kbhit()
#define gtc() getchar()


#elif _WIN32
#include "windows/windowsFunctions.h"

#include <conio.h>
#include <windows.h>

#define CLEARSCREEN system("cls")
#define CHECKKEY _kbhit()
#define NBGETCHAR getch()

#define kbh() _kbhit()
#define gtc() _getch()
#define pts() _cputs()

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


FILE *file;

///
/// FUNZIONI GENERALI
///

// Salva nel file di salvataggio dati del personaggio + stage + abilita'
void savenow(pg personaggio, char nomefile[])
{
    file=fopen(nomefile, "w");
    fprintf(file, "%d\n%s\n%d %d %d %d %d %d %d %d %d %d\n", personaggio.posizione, personaggio.name, personaggio.lvl, personaggio.exp, personaggio.rexp, personaggio.hp, personaggio.mhp, personaggio.sp, personaggio.msp, personaggio.spd, personaggio.pow, personaggio.mind);
    fprintf(file, "%d %d %d %d %d %d\n%d %d %f %f", personaggio.abilities[0], personaggio.abilities[1], personaggio.abilities[2], personaggio.abilities[3], personaggio.abilities[4], personaggio.abilities[5], personaggio.healingKits, personaggio.deaths, personaggio.powRes, personaggio.mindRes);
    printf("\n\033[35mSalvataggio Completato!\033[0m\n");
    fclose(file);
}

// Carica il file di salvataggio su una struct Personaggio
pg loadnow(pg personaggio, char nomefile[])
{
    file=fopen(nomefile, "r");
    fscanf(file, "%d\n", &personaggio.posizione);
    fscanf(file, "%[^\n]s\n", personaggio.name);
    fscanf(file, "%d", &personaggio.lvl);
    fscanf(file, "%d", &personaggio.exp);
    fscanf(file, "%d", &personaggio.rexp);
    fscanf(file, "%d", &personaggio.hp);
    fscanf(file, "%d", &personaggio.mhp);
    fscanf(file, "%d", &personaggio.sp);
    fscanf(file, "%d", &personaggio.msp);
    fscanf(file, "%d", &personaggio.spd);
    fscanf(file, "%d", &personaggio.pow);
    fscanf(file, "%d\n", &personaggio.mind);

    fscanf(file, "%d", &personaggio.abilities[0]);
    fscanf(file, "%d", &personaggio.abilities[1]);
    fscanf(file, "%d", &personaggio.abilities[2]);
    fscanf(file, "%d", &personaggio.abilities[3]);
    fscanf(file, "%d", &personaggio.abilities[4]);
    fscanf(file, "%d\n", &personaggio.abilities[5]);

    fscanf(file, "%d", &personaggio.healingKits);
    fscanf(file, "%d", &personaggio.deaths);
    fscanf(file, "%f", &personaggio.powRes);
    fscanf(file, "%f", &personaggio.mindRes);
    printf("\n\033[35mCaricamento del salvataggio \"%s\"... Completato!\033[0m\n", personaggio.name);
    fclose(file);
    return personaggio;
}

// Cancella definitavemnte il file di salvataggio
// e printa su schermo l'animazione di game over
pg gameover(pg personaggio, char savefile[])
{
    printPgStats(personaggio);
    printf("\n\n\033[31;6mAfter fighting for %d rooms,\n   %s lies on the floor, defeated...\n\n\033[0m        \033[51;31;5;3mG A M E  O V E R\n\n", personaggio.posizione, personaggio.name);
    printf("\033[0m");
    personaggio.deaths++;
    personaggio = resetPg(personaggio);
    savenow(personaggio, savefile);
    return personaggio;
}

// Legge i dati del file di salvataggio
pg resetPg(pg personaggio)
{
    printf("Come si chiamera' la tua prossima incarnazione?\n: ");
    scanf("%[^\n]s", personaggio.name);
    fflush(stdin);
    personaggio.mhp=1;
    personaggio.msp=1;
    personaggio.sp=1;
    personaggio.hp=1;
    personaggio.spd=1;
    personaggio.pow=1;
    personaggio.mind=1;
    personaggio.posizione=1;
    personaggio.healingKits=5;
    personaggio.powRes = 0;
    personaggio.mindRes = 0;

    personaggio.exp=2000;
    int oldLevel = personaggio.lvl;
    personaggio=newlevel(personaggio);
    personaggio.exp=personaggio.deaths*25+oldLevel/2;
    personaggio.exp = 0;
    personaggio.lvl = 10;

    personaggio.rexp=2000;
    personaggio = newResistanceLevel(personaggio);

    if(personaggio.pow > personaggio.mind){
        personaggio.abilities[0]=1;
        personaggio.abilities[1]=15;
        personaggio.abilities[2]=0;
        personaggio.abilities[3]=0;
        personaggio.abilities[4]=0;
        personaggio.abilities[5]=0;
    }
    else if(personaggio.pow < personaggio.mind){
        personaggio.abilities[0]=2;
        personaggio.abilities[1]=3;
        personaggio.abilities[2]=0;
        personaggio.abilities[3]=0;
        personaggio.abilities[4]=0;
        personaggio.abilities[5]=0;
    }
    else{
        personaggio.abilities[0]=1;
        personaggio.abilities[1]=2;
        personaggio.abilities[2]=14;
        personaggio.abilities[3]=0;
        personaggio.abilities[4]=0;
        personaggio.abilities[5]=0;
    }



    return personaggio;
}

pg newResistanceLevel(pg personaggio){
        cleanS();
    int i=0, e=0;
    for(; personaggio.rexp>=100; personaggio.rexp-=100, i++) {}
            printf("\x1b[%d;%dH", 0, 0);
            printf("\n\n\033[93;3mHai %d punti da spendere!\n\033[23mInserire il numero corrispondente ad una delle statistiche indicate:\n\033[0m", i);
            printf("\n-1- Resistenza Fisica > ");
            printaBarra(personaggio.powRes, 175, 'y');
            printf("\n-2- Resistenza Magica > ");
            printaBarra(personaggio.mindRes, 175, 'y');
            printPgStats(personaggio);
    while(i>0)
    {
        #ifdef _WIN32
        _cputs( "" );
        #endif

        if(kbh())
        {
            switch(gtc())
            {
            case '1':
                personaggio.powRes++;
                i--;
                e++;
                break;
            case '2':
                personaggio.mindRes++;
                i--;
                e++;
                break;
            default:
                break;
            }
            printf("\x1b[%d;%dH", 0, 0);
            printf("\n\n\033[93;3mHai %d punti da spendere!\n\033[23mInserire il numero corrispondente ad una delle statistiche indicate:\n\033[0m", i);
            printf("\n-1- Resistenza Fisica > ");
            printaBarra(personaggio.powRes, 175, 'y');
            printf("\n-2- Resistenza Magica > ");
            printaBarra(personaggio.mindRes, 175, 'y');
            printPgStats(personaggio);
        }
    }

    if(personaggio.powRes > 175){
        personaggio.powRes = 175;
    }
    if(personaggio.mindRes > 175){
        personaggio.mindRes = 175;
    }

    cleanS();
    return personaggio;
}

// Controlla se si ha un numero di EXP maggiore di un multiplo di 100
// per ogni multiplo superato da 1 un punto da aggiungere alle stats
pg newlevel(pg personaggio)
{
    cleanS();
    int i=0, a=0, b=0, c=0, d=0, e=0;
    for(; personaggio.exp>=100; personaggio.exp-=100, i++, personaggio.lvl++) {}
            cleanS();
            printf("\x1b[%d;%dH", 0, 0);
            printf("\n\n\033[93;3mHai %d punti da spendere!\n\033[23mInserire il numero corrispondente ad una delle statistiche indicate:\n\033[0m", i);
            printf("-1- Punti Vita        > ");
            printaBarra(personaggio.mhp, personaggio.lvl, 'y');
            printf("\n-2- Punti Mana        > ");
            printaBarra(personaggio.msp, personaggio.lvl, 'y');
            printf("\n-3- Velocita'         > ");
            printaBarra(personaggio.spd, personaggio.lvl, 'y');
            printf("\n-4- Forza fisica      > ");
            printaBarra(personaggio.pow, personaggio.lvl, 'y');
            printf("\n-5- Forza Magica      > ");
            printaBarra(personaggio.mind, personaggio.lvl, 'y');
            printPgStats(personaggio);
    while(i>0)
    {
        personaggio.hp=personaggio.mhp;
        personaggio.sp=personaggio.msp;

        #ifdef _WIN32
        _cputs( "" );
        #endif
        if(kbh())
        {
            switch(gtc())
            {
            case '1':
                personaggio.mhp++;
                i--;
                a++;
                break;
            case '2':
                personaggio.msp++;
                i--;
                b++;
                break;
            case '3':
                personaggio.spd++;
                i--;
                c++;
                break;
            case '4':
                personaggio.pow++;
                i--;
                d++;
                break;
            case '5':
                personaggio.mind++;
                i--;
                e++;
                break;
            default:
                break;
            }
            printf("\x1b[%d;%dH", 0, 0);
            printf("\n\n\033[93;3mHai %d punti da spendere!\n\033[23mInserire il numero corrispondente ad una delle statistiche indicate:\n\033[0m", i);
            printf("-1- Punti Vita        > ");
            printaBarra(personaggio.mhp, personaggio.lvl, 'y');
            printf("\n-2- Punti Mana        > ");
            printaBarra(personaggio.msp, personaggio.lvl, 'y');
            printf("\n-3- Velocita'         > ");
            printaBarra(personaggio.spd, personaggio.lvl, 'y');
            printf("\n-4- Forza fisica      > ");
            printaBarra(personaggio.pow, personaggio.lvl, 'y');
            printf("\n-5- Forza Magica      > ");
            printaBarra(personaggio.mind, personaggio.lvl, 'y');
            printPgStats(personaggio);
        }
    }
    cleanS();
    personaggio.hp=personaggio.mhp;
    personaggio.sp=personaggio.msp;
    return personaggio;
}

// Scrive su schermo i dati del giocatore
void printPgStats(pg personaggio)
{
    printf("\n\033[32;1;3;4m     %s \n\033[0m Livello %d  \nEsperienza %d\n    ", personaggio.name, personaggio.lvl, personaggio.exp);
    int i=personaggio.exp;
    while(i>100)
    {
        i-=100;
    }
    printaBarra(i, 100, 'g');
    printf("\nEsperienza Difensiva %d\n    ", personaggio.rexp);
    i=personaggio.rexp;
    while(i>100)
    {
        i-=100;
    }
    printaBarra(i, 100, 'm');

    printf("\n\n Stanza %d\n Reincarnazione %d\n\n Vita %d/%d\n    ", personaggio.posizione, personaggio.deaths, personaggio.hp, personaggio.mhp);
    printaBarra(personaggio.hp, personaggio.mhp, 'r');
    printf("\n Mana %d/%d\n    ", personaggio.sp, personaggio.msp);
    printaBarra(personaggio.sp, personaggio.msp, 'b');
    printf("\n Velocita' %d\n Forza Fisica %d\n Forza Magica %d", personaggio.spd, personaggio.pow, personaggio.mind);
    printf("\n\n Resistenza Fisica %0.1lf%%\n Resistenza Magica %0.1lf%%\n\n Medikit in possesso %d\n\n\n", (personaggio.powRes - 100), (personaggio.mindRes - 100) , personaggio.healingKits);
}

// menu principale
pg menuavventura(pg personaggio, char salvataggio[], char fileattacco[], char filenemici[])
{
    int choo=-1;
    //while(choo<1 || choo>4){
    printf("\n\033[93;3;4m     Menu \033[0m\n");
    printf("-1- Dati Personaggio\n-2- Sali di Livello\n-3- Potenzia Armatura\n-4- Abilita'\n-5- Sali al prossimo piano\n\n-6- Salva\n-7- \033[31mEsci\033[0m\n: ");
    scanf("%d", &choo);
    fflush(stdin);
    //}
    cleanS();
    switch(choo)
    {
    case 1:
        printPgStats(personaggio);
        break;
    case 2:
        personaggio = newlevel(personaggio);
        break;
    case 3:
        personaggio = newResistanceLevel(personaggio);
        break;
    case 4:
        mostraattacchi(personaggio, fileattacco);
        break;
    case 5:
        personaggio=esplorazione(personaggio, salvataggio, fileattacco, filenemici);
        break;
    case 6:
        savenow(personaggio, salvataggio);
        break;
    case 7:
        exit(0);
        break;
    case 118:
        personaggio=menudebug(personaggio, salvataggio, fileattacco, filenemici);
        break;
    default:
        break;
    }
    choo=-1;
    return personaggio;
}

// menu debug
pg menudebug(pg personaggio, char salvataggio[], char fileattacco[], char filenemici[])
{
    int choo=-1;
    while(choo<0 || choo>4)
    {
        printf("\n\033[31;3;4;51m Pronto? Qui il centralino del 118, mi dica!\033[0m\n");
        printf("-0- Exit Debug\n-1- Kill yourself\n-2- New Ability\n-3- Add 10 lvls\n-4- Set 10000 HP and 10000 MHP");
        scanf("%d", &choo);
        fflush(stdin);
    }
    cleanS();
    switch(choo)
    {
    case 0:
        break;
    case 1:
        personaggio.hp=0;
        break;
    case 2:
        personaggio=newability(personaggio, fileattacco);
        break;
    case 3:
        printf("EXP = %d", personaggio.exp);
        personaggio.exp+=1500;
        printf("=> EXP = %d\n", personaggio.exp);
        break;
    case 4:
        personaggio.hp=10000;
        personaggio.mhp=10000;
        break;
    default:
        break;
    }
    return personaggio;
}


///
/// FIGHT SYSTEM
///

pg fight(pg personaggio, char fileattacco[], char filenemici[])
{
    int randNum=1, initiative;
    while(loadEnemy(randNum, filenemici).lvl < personaggio.lvl - 20 || loadEnemy(randNum, filenemici).lvl > personaggio.lvl)
    {
        randNum=(rand() % getFileLinesNumber(filenemici)/2 + 1);
        //printEnemy(loadEnemy(randNum, filenemici));
    }
    printf("\n\nUn essere ti attacca! Si tratta di . . .\n\n");
    enem enemy=loadEnemy(randNum, filenemici);
    fflush(stdin);
    printEnemy(enemy);

    if(enemy.spd >= personaggio.spd){
        initiative = 0;
        printf("\nL'avversario e' piu' veloce!");
    }
    else{
        initiative = 1;
        printf("\nSei piu' veloce!");
    }


    while(1)
    {
        if(initiative == 0){
            if(personaggio.hp >= 1){
                personaggio = enemyAttack(personaggio, &enemy, fileattacco);
            }
            if(enemy.hp >= 1){
                enemy = menudegiocatore(&personaggio, enemy, fileattacco);
            }
        }
        else{
            if(enemy.hp >= 1){
                enemy = menudegiocatore(&personaggio, enemy, fileattacco);
            }
            if(personaggio.hp >= 1){
                personaggio = enemyAttack(personaggio, &enemy, fileattacco);
            }
        }

        if(enemy.hp<=0 || personaggio.hp<=0)
        {
            if(personaggio.hp>personaggio.mhp)
            {
                personaggio.hp=personaggio.mhp;
            }


            if(personaggio.hp>0){
                if(enemy.exp-((personaggio.lvl)-enemy.lvl) > 0){
                    printSchermataBarreVita(personaggio, enemy);
                    printf("\n\n\033[33m   HAI VINTO!\n     Hai guadagnato %d EXP e %d Defence EXP!!\033[0m\n", enemy.exp-((personaggio.lvl)-enemy.lvl), (enemy.exp-((personaggio.lvl)-enemy.lvl))/2);
                    personaggio.exp += enemy.exp-((personaggio.lvl)-enemy.lvl);
                    personaggio.rexp += (enemy.exp-((personaggio.lvl)-enemy.lvl))/2;
                }
                else {
                    printSchermataBarreVita(personaggio, enemy);
                    printf("\n\n\033[33m   HAI VINTO!\033[0m\n\n");
                    personaggio.exp += 0;
                }
            }



            return personaggio;
        }
    }
}

pg enemyAttack(pg personaggio, enem* nemico, char fileattacco[]){

        int enemRandAbility, damage;
        attack attaccoAttivo;
        enem enemy = *nemico;
        enemRandAbility = rand() % 6 + 1;
    if(enemy.hp > 0){

        attaccoAttivo = prendidatiattacco(enemy.abilities[enemRandAbility-1], fileattacco);
        if(enemy.sp-attaccoAttivo.spCost>-1)
        {
            printf("\nL'avversario usa...\n\n");
            printAbility(attaccoAttivo);
            damage=0;

            damage+=(attaccoAttivo.multdamagepow*enemy.pow+attaccoAttivo.multdamagemind*enemy.mind)/3;

            switch(attaccoAttivo.target){
                case 0:
                    enemy.hp-=damage;
                    break;
                case 1:
                    if(damage * (1.0 -(personaggio.powRes - 100.0)/ 100.0)  > 0){
                        personaggio.hp -= damage * (1.0 -(personaggio.powRes - 100.0)/ 100.0);
                        printf("\nE ti provoca %d * %0.1lf = %0.1lf di danno",  damage, 1.0 - ( personaggio.powRes - 100.0 ) / 100.0, damage * (1.0 -(personaggio.powRes - 100.0)/ 100.0));
                    }
                    else{
                        printf("\nMa non ti fa nulla...");
                    }
                    break;
                case 2:
                    if(damage * (1.0 -(personaggio.mindRes - 100.0)/ 100.0)){
                        personaggio.hp -= damage * (1.0 -(personaggio.mindRes - 100.0)/ 100.0);
                        printf("\nE ti provoca %d * %0.1lf = %0.1lf di danno",  damage, (1.0 -(personaggio.mindRes - 100.0)/ 100.0), damage * (1.0 - (personaggio.mindRes - 100.0)/ 100.0));
                    }
                    else{
                        printf("\nMa non ti fa nulla...");
                    }
                    break;
                case 3:
                    personaggio.hp -= damage;
                    printf("\nE ti provoca %d di danno", damage);
                    break;
                default:
                    abilitySelector(enemy);
                    break;
            }

            if(enemy.sp - attaccoAttivo.spCost > enemy.msp){
                enemy.sp = enemy.msp;
            }
            else{
                enemy.sp-=attaccoAttivo.spCost;
            }
        }
        else
        {
            printf("L'avversario non ha le forze per fare cio' che vuol fare!\n");
        }
    *nemico = enemy;
    }
    return personaggio;
}

void printEnemy(enem personaggio)
{
    printf("\033[36;1;3;4m     %s \n\033[0m Livello %d\n\n Velocita' %d\n Forza Fisica %d\n Forza Magica %d\n Resistenza Fisica %0.1f%%\n Resistenza Magica %0.1f%%\n\n", personaggio.name, personaggio.lvl, personaggio.spd, personaggio.pow, personaggio.mind, (personaggio.powRes-100), (personaggio.mindRes - 100));
}

// Carica il file di salvataggio su una struct Personaggio
enem loadEnemy(int indexEnemyInList, char nomefile[])
{
    //printf("-----DEBUG-----\nEntity called index = %d\n", indexEnemyInList);
    enem personaggio;
    int i=0;
    file=fopen(nomefile, "r");
    do
    {
        i++;
        fflush(stdin);
        fscanf(file, "%[^\n]s\n", personaggio.name);
        //printf("Index = %d - Enemy name = %s\n",  i, personaggio.name);
        fscanf(file, "%d", &personaggio.lvl);
        fscanf(file, "%d", &personaggio.exp);

        fscanf(file, "%d", &personaggio.hp);
        fscanf(file, "%d", &personaggio.mhp);
        fscanf(file, "%d", &personaggio.sp);
        fscanf(file, "%d", &personaggio.msp);

        fscanf(file, "%d", &personaggio.spd);
        fscanf(file, "%d", &personaggio.pow);
        fscanf(file, "%d", &personaggio.mind);

        fscanf(file, "%f", &personaggio.powRes);
        fscanf(file, "%f", &personaggio.mindRes);

        fscanf(file, "%d", &personaggio.abilities[0]);
        fscanf(file, "%d", &personaggio.abilities[1]);
        fscanf(file, "%d", &personaggio.abilities[2]);
        fscanf(file, "%d", &personaggio.abilities[3]);
        fscanf(file, "%d", &personaggio.abilities[4]);
        fscanf(file, "%d\n", &personaggio.abilities[5]);
    }
    while(i!=indexEnemyInList);
    fclose(file);
    cleanS();
    return personaggio;
}

// Prende i dati dell'abilita' dal file delle abilita'
attack prendidatiattacco(int numero, char fileattacco[])
{
    attack attacco;
    //printf("%d", numero);
    file=fopen(fileattacco, "r");
    for(int i=-1; i<numero; i++)
    {
        fscanf(file, "%[^\n]s\n", attacco.name);
        fscanf(file, "%f", &attacco.multdamagepow);
        fscanf(file, "%f", &attacco.multdamagemind);
        fscanf(file, "%d\n", &attacco.spCost);
        fscanf(file, "%d\n", &attacco.target);
        //printf("\n%s %f %f %d\n", attacco.name, attacco.multdamagepow, attacco.multdamagemind, attacco.spCost);
    }
    fclose(file);
    return attacco;
}

// prende un'abilita' casuale, la mostra al giocatore e da la possibilita' di
// sovrascrivere in uno slot abilita' del giocatore il numero dell'abilita'
pg newability(pg personaggio, char fileattacco[])
{
    int choo=-1, abilitynumber;
    attack abilitydata;
    abilitynumber=rand() % getFileLinesNumber(fileattacco)/2 +1;
    abilitydata=prendidatiattacco(abilitynumber, fileattacco);
    while(choo<1 || choo>7)
    {
        printf("\n\033[36;1;3;4m      Nuova abilita'\033[0m\n");
        printAbility(abilitydata);
        mostraattacchi(personaggio, fileattacco);
        printf("\nVuoi inserire l'abilita' in uno slot?");
        printf("\n-1/6- Slot Selezionato e Conferma\n-7- Annulla\n: ");
        scanf("%d", &choo);
        fflush(stdin);
    }
    switch(choo)
    {
    case 1:
        personaggio.abilities[0]=abilitynumber;
        break;
    case 2:
        personaggio.abilities[1]=abilitynumber;
        break;
    case 3:
        personaggio.abilities[2]=abilitynumber;
        break;
    case 4:
        personaggio.abilities[3]=abilitynumber;
        break;
    case 5:
        personaggio.abilities[4]=abilitynumber;
        break;
    case 6:
        personaggio.abilities[5]=abilitynumber;
        break;
    case 7:
        break;
    default:
        printf("Errore in New Ability");
        exit(1);
    }
    return personaggio;
}

int getFileLinesNumber(char nomefile[])
{
    int i=0;
    file=fopen(nomefile, "r");
    while(!feof(file))
    {
        if(fgetc(file) == '\n')
        {
            i++;
        }
    }
    fclose(file);
    return i;
}

// mostra sullo schermo una sola abilita'
void printAbility(attack attacco)
{
    printf("\033[36m%s\033[0m\n Danni Fisici > %0.1lf\n Danni Magici > %0.1lf\n Costo > %d\n", attacco.name, attacco.multdamagepow/3, attacco.multdamagemind/3, attacco.spCost);
    switch(attacco.target){
        case 0:
            printf(" Tipologia > Altro\n");
            break;
        case 1:
            printf(" Tipologia > Fisico\n");
            break;
        case 2:
            printf(" Tipologia > Magico\n");
            break;
        case 3:
            printf(" Tipologia > Neutro\n");
            break;
        default:
            break;
    }
}

// Mostra sullo schermo la lista delle abilita' del giocatore
void mostraattacchi(pg personaggio, char fileattacco[])
{
    attack attacco[6];
    printf("\n\033[36;1;3;4m   Lista Abilita'\033[0m\n");
    for(int i=0; i<6; i++)
    {
        attacco[i]=prendidatiattacco(personaggio.abilities[i], fileattacco);
        if(personaggio.abilities[i]!=0)
        {
            printf("\033[35m-%d- \033[0m", i+1);
            printAbility(prendidatiattacco(personaggio.abilities[i], fileattacco));
            printf("\n");
        }
    }
}

///
/// EXPL
///

pg esplorazione(pg personaggio, char salvataggio[], char fileattacco[], char filenemici[])
{
    int piano[LATOPVE][LATOPOR];
    int randEnemyNum=(rand() % 5 + 1), randMedikitNum=(rand() % 4 + 1), j=0;
    coordinate nemico[randEnemyNum];
    coordinate medikit[randMedikitNum];
    coordinate scroll;

    for(int i=0; i<randEnemyNum; i++)
    {
        nemico[i].e=1;
        if(nemico[i].e==1)
        {
            nemico[i].x=rand()% LATOPOR;
            nemico[i].y=rand()% LATOPVE;
        }
    }

    for(int i=0; i<randMedikitNum; i++)
    {
        medikit[i].e=1;
        if(medikit[i].e==1)
        {
            medikit[i].x=rand()% LATOPOR;
            medikit[i].y=rand()% LATOPVE;
        }
    }

    if(rand()%5==1)
    {
        scroll.e=1;
    }
    if(scroll.e==1)
    {
        scroll.x=rand()% LATOPOR;
        scroll.y=rand()% LATOPVE;
    }

    do
    {
        for(int i=0; i<LATOPVE; i++)
        {
            for(int j=0; j<LATOPOR; j++)
            {
                piano[i][j]=0;
            }
        }
        printf("\x1b[%d;%dH", 0, 0);

        #ifdef _WIN32
        _cputs( "" );
        #endif
        if(kbh())
        {
            switch(gtc())
            {
            case 'w':
            case 'W':
            case '8':
                if(personaggio.p.y!=0)
                {
                    personaggio.p.y--;
                }
                break;
            case 'a':
            case 'A':
            case '4':
                if(personaggio.p.x!=0)
                {
                    personaggio.p.x--;
                }
                break;
            case 's':
            case 'S':
            case '2':
                if(personaggio.p.y!=LATOPVE-1)
                {
                    personaggio.p.y++;
                }
                break;
            case 'd':
            case 'D':
            case '6':
                if(personaggio.p.x!=LATOPOR-1)
                {
                    personaggio.p.x++;
                }
                break;
            case 'e':
            case 'E':
            case '9':
                cleanS();
                printPgStats(personaggio);
                stop();
                cleanS();
                break;
            default:
                break;
            }
            for(int i=0; i<randEnemyNum; i++)
            {
                if(nemico[i].e==1)
                {
                    if(rand()% 2 == 1)
                    {
                        if(nemico[i].x>personaggio.p.x)
                        {
                            nemico[i].x--;
                        }
                        else if(nemico[i].x<personaggio.p.x)
                        {
                            nemico[i].x++;
                        }
                        else if(nemico[i].y>personaggio.p.y)
                        {
                            nemico[i].y--;
                        }
                        else if(nemico[i].y<personaggio.p.y)
                        {
                            nemico[i].y++;
                        }
                    }
                    if(nemico[i].x == personaggio.p.x && nemico[i].y == personaggio.p.y)
                    {
                        nemico[i].e=0;
                        personaggio = fight(personaggio, fileattacco, filenemici);
                        if (personaggio.hp<=0)
                        {
                            personaggio = gameover(personaggio, salvataggio);
                        }
                        stop();
                        cleanS();
                    }
                }

            }
            for(int i=0; i<randMedikitNum; i++)
            {
                if(medikit[i].e==1)
                {
                    if(medikit[i].x == personaggio.p.x && medikit[i].y == personaggio.p.y)
                    {
                        medikit[i].e=0;
                        personaggio.healingKits++;
                    }
                }
            }
            if(scroll.e==1)
            {
                if(scroll.x == personaggio.p.x && scroll.y == personaggio.p.y)
                {
                    scroll.e=0;
                    cleanS();
                    personaggio = newability(personaggio, fileattacco);
                    cleanS();
                }
            }
        }
        for(int i=0; i<randEnemyNum; i++)
        {
            if(nemico[i].e==1)
            {
                piano[nemico[i].y][nemico[i].x]=2;
            }
        }
        for(int i=0; i<randMedikitNum; i++)
        {
            if(medikit[i].e==1)
            {
                piano[medikit[i].y][medikit[i].x]=3;
            }
        }
        if(scroll.e==1)
        {
            piano[scroll.y][scroll.x]=4;
        }
        piano[personaggio.p.y][personaggio.p.x]=1;
        j = 0;
        for(int i=0; i<randEnemyNum; i++){
            if(nemico[i].e==0)
            {
                j++;
            }
        }
        if(j>=randEnemyNum){
            break;
        }
        printMatrice(piano);
    }
    while(1);
    personaggio.posizione++;
    return personaggio;
}

void printMatrice(int matrice[LATOPVE][LATOPOR])
{
#ifdef _WIN32
    int showFlag=0;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
#endif // _WIN32
    for(int i=0; i<LATOPVE; i++)
    {
        printf("\n     ");
        for(int j=0; j<LATOPOR; j++)
        {
            switch(matrice[i][j])
            {
            #ifdef _WIN32
            case 0:  // TERRENO
                printf("\033[37;100m%c%c\033[0m", 177, 177);
                break;
            case 1:  // GIOCATORE
                printf("\033[36m%c%c\033[0m", 177, 177);
                break;
            case 2:  // NEMICO
                printf("\033[31;100m%c%c\033[0m", 177, 177);
                break;
            case 3:  // MEDIKIT
                printf("\033[32;100mMK\033[0m");
                break;
            case 4:  // ABILITA'
                printf("\033[34;100mAB\033[0m");
                break;
            default:
                break;
            #elif __linux__
            case 0:  // TERRENO
                printf("\033[37;100m##\033[0m");
                break;
            case 1:  // GIOCATORE
                printf("\033[36m%%%%\033[0m");
                break;
            case 2:  // NEMICO
                printf("\033[31;100mZZ\033[0m");
                break;
            case 3:  // MEDIKIT
                printf("\033[32;100mMK\033[0m");
                break;
            case 4:  // ABILITA'
                printf("\033[34;100mAB\033[0m");
                break;
            default:
                break;
            #endif
            }
        }
    }
    printf("\n\n   Movimento > {W,A,S,D} o {8,4,2,6}\n  Statistiche Personaggio > {E} o {9}\n\n");
}

///
/// FUNZIONI UTILITA' PORTABILI
///



void printSchermataBarreVita(pg personaggio, enem nemico)
{
    printf("\n\n%s\n", personaggio.name);
    printaBarra(personaggio.hp, personaggio.mhp, 'r');
    printf("> %04d ", personaggio.hp);
    printf("  V/  ");
    printaBarra(nemico.hp, nemico.mhp, 'm');
    printf("\n");
    printaBarra(personaggio.sp, personaggio.msp, 'b');
    printf("> %04d ", personaggio.sp);
    printf("  /S  ");
    printaBarra(nemico.sp, nemico.msp, 'c');
    printf("\n                         %s", nemico.name);
}

