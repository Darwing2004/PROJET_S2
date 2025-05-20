#include <stdio.h>
#include <stdlib.h>
#define taille_max 10

typedef struct ressources
{
    int quantite;
    char type[50];
} ressources;

typedef struct Bat
{
    char type[50];
    int ID_Bat;
    int etage;
    int x;
    int y;
    int hauteur;
    int age;
    int capacite;
    int etat; // allant de 0 à 100
    ressources bat_stock;
} Bat;

typedef struct Sommet_ville
{
    int ID;
    char type[50];
    char nom[50];
    int population;
    Bat *batiment;
    int n_bats;
    int etat;

} Sommet_ville;

typedef struct Tab_sommets
{
    Sommet_ville *sommets;
    int n_sommets;
    Bat *batiments;
    int n_bats;
} Tab_sommets;

typedef struct Route
{
    int distance;
    int etat;
    int capacité;
} Route;

typedef struct Graphe
{
    Sommet_ville *sommets;
    Tab_sommets *sommets_TAB;
    Route **chemins;

} Graphe;

// Fonction de chaque fichier .c

//     Mission1.c
void initialiser_graphe_entier(Graphe *G);
void creation_route(Graphe *G, int id_depart, int id_arrivee, int distance_voulue);
void initialiser_tableau_batiment(Tab_sommets *tableau_bats_sommets, int nombre);
void ajouter_bat(Bat batiment_quelconque, Tab_sommets *tableau_bats_sommets, Graphe *G, int id_desire);
void supprimer_Bat(Tab_sommets *tableau_bats_sommets, Bat *bat_a_supprimer, Sommet_ville *sommet_bat_supp);
void ajouter_sommet(Tab_sommets *sommet, Graphe *G, Sommet_ville sommet_quelconque);
void seisme(Sommet_ville *sommet_seisme, int seisme_impact, Tab_sommets *sommet, Graphe *G);
void verifier_accessibilite(Graphe *G, int ID_sommet_debut);
void afficher_route(Graphe *G, int ID_sommet_debut);