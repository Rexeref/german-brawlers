#include "gameFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
// #include <stropts.h>

// code for linux
#define CLEARSCREEN system("clear")
#define CHECKKEY
#define NBGETCHAR

#define kbh() kbhit()
#define gtc() getchar()

enem menudegiocatore(pg* appoggio, enem nemico, char fileattacco[])
{
    int choo = -1, itemUsed=0;
    attack attaccoAttivo;
    pg personaggio = *appoggio;
    double damage=0;
    while(choo<0 || choo>6)
    {
        choo=-1;
        while(choo<0 || choo>10)
        {
            //printf("\nGiocatore HP %d/%d Nemico HP %d/%d\n", personaggio.hp, personaggio.mhp, nemico.hp, nemico.mhp);
            printSchermataBarreVita(personaggio, nemico);
            printf("\n\n\033[35;3;4;51m Combattimento!\033[0m\n");
            printf("-0- Recover SP \n-1/6- Choose ability\n-7- Player Data\n-8- Enemy Data\n-9- Abilities List\n-10- Use Medikit\n\n: ");
            fflush(stdin);
            scanf("%d", &choo);
            fflush(stdin);
        }
        cleanS();
        switch(choo)
        {
        case 0:
            if(personaggio.lvl/5 + personaggio.sp <= personaggio.msp && personaggio.healingKits > 0)
            {
                personaggio.sp+=personaggio.lvl/5;
                personaggio.healingKits--;
                printf("\nUtilizzi un medikit. Ti senti rinvigorito!\nHai Recuperato %d sp\n", personaggio.lvl/5);
            }
            else if (personaggio.lvl/5 + personaggio.sp > personaggio.msp && personaggio.healingKits > 0)
            {
                personaggio.sp=personaggio.msp;
                personaggio.healingKits--;
                printf("\nUtilizzi un medikit.\nNon ti sei mai sentito tanto bene mentalmente!\n");
            }
            else
            {
                printf("\nNon hai medikit!\n");
            }
            attaccoAttivo=prendidatiattacco(0, fileattacco);
            itemUsed=1;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            attaccoAttivo=prendidatiattacco(personaggio.abilities[choo-1], fileattacco);
            break;
        case 7:
            printPgStats(personaggio);
            break;
        case 8:
            printEnemy(nemico);
            break;
        case 9:
            mostraattacchi(personaggio, fileattacco);
            break;
        case 10:
            if(personaggio.lvl/10 + personaggio.hp <= personaggio.mhp && personaggio.healingKits > 0)
            {
                personaggio.hp+=personaggio.lvl/10;
                attaccoAttivo=prendidatiattacco(0, fileattacco);
                personaggio.healingKits--;
                printf("\nUtilizzi un medikit. Ti senti rinvigorito!\nHai Recuperato %.0f hp\n", round(personaggio.lvl/10));
            }
            else if (personaggio.lvl/10 + personaggio.hp > personaggio.mhp && personaggio.healingKits > 0)
            {
                personaggio.hp=personaggio.mhp;
                personaggio.healingKits--;
                printf("\nUtilizzi un medikit.\nNon ti sei mai sentito tanto bene fisicamente!\n");
            }
            else
            {
                printf("\nNon hai medikit!\n");
            }
            attaccoAttivo=prendidatiattacco(0, fileattacco);
            itemUsed=1;
            break;
        default:
            break;
        }
    }
    if(itemUsed==1) {}
    else if(personaggio.sp-attaccoAttivo.spCost>-1)
    {
        printf("\nUsi . . .\n\n");
        printAbility(attaccoAttivo);
        damage=0;
        damage+=(attaccoAttivo.multdamagepow*personaggio.pow+attaccoAttivo.multdamagemind*personaggio.mind)/3;

            switch(attaccoAttivo.target){
                case 0:
                    personaggio.hp-=damage;
                    break;
                case 1:
                    if(damage * (1.0 -(nemico.powRes - 100.0)/ 100.0) > 0){
                        nemico.hp -= damage * (1.0 -(nemico.powRes - 100.0)/ 100.0);
                        printf("\nE gli provochi %0.1lf * %0.1lf = %0.1lf di danno\n",  damage, (1.0 -(nemico.powRes - 100.0)/ 100.0), damage * (1.0 -(nemico.powRes - 100.0)/ 100.0));
                    }
                    else{
                        printf("\nMa non gli fai nulla...");
                    }
                    break;
                case 2:
                    if(damage * (1.0 -(nemico.mindRes - 100.0)/ 100.0)){
                        nemico.hp -= damage * (1.0 -(nemico.mindRes - 100.0)/ 100.0);
                        printf("\nE gli provochi %0.1lf * %0.1lf = %0.1lf di danno\n", damage, (1.0 -(nemico.mindRes - 100.0)/ 100.0), damage * (1.0 -(nemico.mindRes - 100.0)/ 100.0));
                    }
                    else{
                        printf("\nMa non gli fai nulla...");
                    }
                    break;
                case 3:
                    nemico.hp -= damage;
                    printf("\nE gli provochi %0.1lf di danno", damage);
                    break;
                default:
                    break;
            }

        if(personaggio.sp-attaccoAttivo.spCost > personaggio.msp){
            personaggio.sp = personaggio.msp;
        }
        else{
            personaggio.sp-=attaccoAttivo.spCost;
        }
    }
    else
    {
        printf("\n\n");
    }
    *appoggio=personaggio;
    return nemico;
}


void cleanS(void)
{
    system("clear");
}

void stop(void)
{
    char inutile;
    printf("\nPremi un tasto per continuare...");
    inutile=getc(stdin);
    printf("%c\r   ", inutile);
    fflush(stdin);
}

void pause(void)
{
    system("sleep 5");
}

void printaBarra(float valore, float max, char color)
{
    printf("[");
    switch(color)
    {
    case 'r':
        printf("\033[31m");
        break;
    case 'b':
        printf("\033[34m");
        break;
    case 'g':
        printf("\033[32m");
        break;
    case 'y':
        printf("\033[33m");
        break;
    case 'm':
        printf("\033[35m");
        break;
    case 'c':
        printf("\033[36m");
        break;
    default:
        printf("\033[0m");
        break;
    }
    if(valore <= 0)
    {
        printf("\033[0m");
        for(int i=0; i<10; i++)
        {
            printf("/");
        }
    }
    else if(valore > max)
    {
        for(int i=0; i<10; i++)
        {
            printf("%c", 177);
        }
        printf("/");
    }
    else
    {
        for(int i=0; i<(valore/max*10); i++)
        {
            printf("/");
        }
        printf("\033[0m");
        for(int i=0; i< 10 - (valore/max*10); i++)
        {
            printf("/");
        }
    }
    printf("]");
}

int kbhit() {
    static const int STDIN = 0;
    int initialized = 0;

    if (! initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}