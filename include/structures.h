#include <stdio.h>
#include <stdlib.h>
#define taille_max 100

typedef struct Bat{
    char type[50];
    char etat_courant[50];
    int ID_Bat;
    int etage;
    int x;
    int y;
    int hauteur;
    int age;
    int capacite;
    int etat;//allant de 0 à 100
    ressources* bat_stock;
}Bat;

typedef struct ressources{
    int quantite;
    char type[50];
}ressources;

typedef struct Sommet_ville{
    int ID;
    char type[50];
    char nom[50];
    int population;
    Bat* batiment;
    int n_bats;

}Sommet_ville;

typedef struct Tab_sommets{
    Sommet_ville* sommets;
    int n_sommets;
    Bat* batiments;
    int n_bats;
}Tab_sommets;

typedef struct Graphe{
    
    Sommet_ville* sommets;
    Tab_sommets* sommets_TAB;
    Route chemins[taille_max][taille_max];

}Graphe;

typedef struct Route{

    int distance;
    int etat;
    int capacité;
    char etat_actuel[50];
}Route;