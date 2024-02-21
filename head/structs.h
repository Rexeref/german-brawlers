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