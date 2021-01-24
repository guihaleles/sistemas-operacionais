// char charactersNames[8][15] = {"Sheldon", "Leonard", "Howard", "Stuart", "Kripke", 
//                                 "Penny", "Bernardette", "Amy"};

typedef struct
{
    char name[15];
    int partnerNumber;
} Character;

typedef struct
{
    char name[50];
    int type;    
} Information;



Character characters[8] = 
{
    { "Sheldon", 7 },
    { "Leonard", 5},
    { "Howard", 6},
    { "Stuart", -1},
    { "Kripke", -1},
    { "Penny", 2},
    { "Bernardette", 3},
    { "Amy", 1}
};

Information informations[] = 
{
    {"quer usar o forno", 1},
    {"começa a esquentar algo", 2},
    {"vai comer", 3},
    {"voltou para o trabalho", 4},
    {"detectou um deadlock, liberando", 5}
};