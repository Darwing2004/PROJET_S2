#ifndef STRUCTURES_H
#define STRUCTURES_H


typedef struct ressources {
    int quantite;
    char type[50];
} ressources;


typedef struct Bat {
    char type[50];
    char etat_courant[50];
    int ID_Bat;
    int etage;
    int x;
    int y;
    int hauteur;
    int age;
    int capacite;
    int etat;  
    ressources* bat_stock; 
} Bat;


typedef struct Sommet_ville {
    int ID;
    char type[50];  
    char nom[50];   
    int population;
    Bat* batiment;  
    int n_bats;     
} Sommet_ville;


typedef struct Route {
    int distance;  
    int etat;      
    int capacité;  
    char etat_actuel[50]; 
} Route;


typedef struct Tab_sommets {
    Sommet_ville* sommets; 
    int n_sommets;         
    Bat* batiments;        
    int n_bats;            
} Tab_sommets;


typedef struct Vehicule {
    int id;            
    int capacite;      
    char urgence[30]; 
    int priorite;     
    int delai_max;    
} Vehicule;


typedef struct Graphe {
    Sommet_ville* sommets;     
    Tab_sommets* sommets_TAB;  
    Route chemins[100][100];   
} Graphe;


#define MAX_VEHICULES 100
extern Vehicule flotte[MAX_VEHICULES];  
extern int n_vehicules;  

#endif
