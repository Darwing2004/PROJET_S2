#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define NOMBRE_BATIMENT 10
#define taille_max 10
#define MAX_VEHICULES 100

extern int chemin_court[taille_max];
extern int longueur_chemin;

typedef struct ressources
{
    int quantite;
    char type[50];
} ressources;

typedef struct Bat
{
    int n_bat;
    int ID_Bat;
    int etage;
    int capacite;
    int etat;
} Bat;

typedef struct Ville
{
    char nom[50];
    int ID;
    int population_max;
    int etat;
    int nb_bat;
    Bat *batiment;
} Ville;

typedef struct Hopitaux
{
    char nom[50];
    int ID;
    int patients;
    int etat;
    int patients_max;
} Hopitaux;

typedef struct Entrepot
{
    ressources stock;
    int ID;
    char nom[50];
    int etat;
} Entrepot;

typedef struct Sommet
{
    Ville ville;
    Hopitaux hopitale;
    Entrepot entrepot;

    //Cordonne X et Y pour la fenetre de Raylib
    int x;
    int y; 
} Sommet;
typedef struct Tableau_sommets
{
    Sommet *sommets;
    int n_sommets;
    int taille_max_sommet;
} Tab_sommets;

// Structure qui représentent les routes
typedef struct Route
{
    int distance;
    int etat;
    int capacité;
} Route;

// Cette structure représente le pays tout entier : tab_sommets stock les viles et route **chemin toute les routes qui connectes les villes entre elle
typedef struct Graphe
{
    Tab_sommets *sommets_TAB;
    Route **chemins;
} Graphe;

typedef struct Vehicule {
    int id;            
    int capacite;      
    char urgence[30]; 
    int priorite;     
    int delai_max;    
} Vehicule;

typedef struct Affectation {
    int id_vehicule;
    int id_destination;
    int est_affecte;
} Affectation;

extern Affectation affectations[MAX_VEHICULES];
extern Vehicule flotte[MAX_VEHICULES];  
extern int n_vehicules;  

// Fonction de chaque fichier .c

//main
void menue_principale(Graphe *mon_graphe);

// Mission1
Graphe *creer_graphe_vide();
void initialiser_graphe_entier(Graphe *G);
void creation_sommet(Graphe *graphe);
void afficher_sommets(Graphe *G);
void generer_route(Graphe *G);
void afficher_routes(Graphe *G);
int seisme(Graphe *G);
void afficher_graphe_global(Graphe *G);
void liberer_graphe(Graphe *G);
const char *type_sommet(Sommet s);

// Mission 2
void dfs_groupes(Graphe *G, int sommet, bool *visite, int *groupe, int id_groupe);
int* identifier_groupes_sommets(Graphe *G, int *nb_groupes);

// Mission 3
int minDistance(int distance[], bool visited[], int n);
void afficher_chemin(Graphe *G, int pred[], int sommet);
void dijkstra(Graphe *graphe, int depart, int destination);
const char *obtenir_nom_sommet(Sommet *s);
void afficher_sommets_dijkstra(Graphe *G);

//Mission 5
void ajouter_vehicule(int capacite, const char *urgence, int priorite, int delai_max);
void trier_vehicules_par_priorite();
void affecter_vehicules(Graphe *G, int ID_sommet_debut);
void afficher_acheminement(Graphe *G, int ID_sommet_debut);

//Raylib
void afficher_graphe_raylib(Graphe *G);
void placer_sommets(Graphe *G);
void afficher_graphe_raylib_dijkstra(Graphe *G);
void afficher_groupes_connexes(Graphe *G);

#endif