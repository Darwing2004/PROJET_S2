#include <stdio.h>
#include <stdlib.h>
#define taille_max 100

typedef struct ressources{
    int quantite;
    char type[50];
}ressources;

typedef struct Route{

    int distance;
    int etat;
    int capacité;
}Route;

typedef struct Bat{
    char type[50];
    int ID_Bat;
    int etage;
    int capacite;
    int etat;//allant de 0 à 100
    ressources bat_stock;
}Bat;


typedef struct Sommet{
    int ID;
    char type[50];
    char nom[50];
    int population;
    Bat* batiment;
}Sommet;

typedef struct Tab_sommets{
    Sommet* sommets;
    int n_sommets;
    Bat* batiments;
    int n_bats;
}Tab_sommets;

typedef struct Graphe{
    
    Sommet* sommets;
    Tab_sommets* sommets_TAB;
    Route chemins[taille_max][taille_max];

}Graphe;

//Fonction

// 1.  Déclaration du graphe
void genererTypes();
void ajouterArc();
void afficherGraphe();