#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include <time.h>

void initialiser_graphe_entier(Graphe* G){
    G->sommets_TAB->n_sommets=0;

    for(int i=0; i<taille_max; i++){
        for(int g=0; g<taille_max; g++){
            G->chemins[i][g].distance=0;
            G->chemins[i][g].etat=0;
            G->chemins[i][g].capacité=0;
        }
    }
}

void creation_route(Graphe* G, int id_depart, int id_arrivee, int distance_voulue){


    srand(time(NULL));
    int capacite_valeurs[]={5,5,6,6,6,6,7,7,7,7,7,8,8,8,9,10};
    int taille_tab_capacite=sizeof(capacite_valeurs)/sizeof(capacite_valeurs[0]);
    int capacite_aleatoire=rand()%taille_tab_capacite;
    int capacite=capacite_valeurs[capacite_aleatoire];


    G->chemins[id_depart][id_arrivee].distance=distance_voulue;
    G->chemins[id_depart][id_arrivee].capacité=capacite;
    G->chemins[id_depart][id_arrivee].etat=50;
    strcpy(G->chemins[id_depart][id_arrivee].etat_actuel, "bon état");
        
}
void initialiser_tableau_batiment(Tab_sommets* tableau_bats_sommets, int nombre){
    tableau_bats_sommets->batiments=malloc(nombre*sizeof(Bat));
    tableau_bats_sommets->n_bats=0;
}
void ajouter_bat(Bat batiment_quelconque, Tab_sommets* tableau_bats_sommets, Graphe* G){
    int i=0;
   
    
    G->sommets[tableau_bats_sommets->n_bats].batiment[i++]=batiment_quelconque;
    tableau_bats_sommets->n_bats=G->sommets->n_bats;
    tableau_bats_sommets->batiments=realloc(tableau_bats_sommets->sommets->batiment, (tableau_bats_sommets->n_bats + 1) * sizeof(Bat));//modifie la taille du tableau au fur et à mesure que l'on ajoute un batiments
    tableau_bats_sommets->batiments[tableau_bats_sommets->n_bats++]=batiment_quelconque;
    G->sommets[tableau_bats_sommets->n_bats].ID=tableau_bats_sommets->n_bats;

}

void supprimer_Bat(Tab_sommets* tableau_bats_sommets, Bat* bat_a_supprimer, Sommet_ville* sommet_bat_supp, Graphe* G){

        for (int i = 0; i < tableau_bats_sommets->n_bats; i++) {
            if (tableau_bats_sommets->batiments[i].ID_Bat == bat_a_supprimer->ID_Bat) {
                for (int j = i; j < tableau_bats_sommets->n_bats - 1; j++) {
                    tableau_bats_sommets->batiments[j] = tableau_bats_sommets->batiments[j + 1];
                }
                tableau_bats_sommets->n_bats--;
                tableau_bats_sommets->batiments = realloc(tableau_bats_sommets->batiments, tableau_bats_sommets->n_bats * sizeof(Bat));
                break;
            }
        }
         
            for (int i = 0; i < sommet_bat_supp->n_bats; i++) {
                if (G->sommets->batiment[i].ID_Bat == bat_a_supprimer->ID_Bat) {
                    for (int j = i; j < sommet_bat_supp->n_bats - 1; j++) {
                        sommet_bat_supp->batiment[j] = sommet_bat_supp->batiment[j + 1];
                    }
                    G->sommets->n_bats--;
                    G->sommets->n_bats = realloc(sommet_bat_supp->batiment, G->sommets->n_bats * sizeof(Bat));
                    break;
                }
            }
    }
    


void ajouter_sommet(Tab_sommets* sommet,Graphe* G, Sommet_ville sommet_quelconque){
    int id=0;

    sommet->sommets=realloc(sommet->sommets, (sommet->n_sommets + 1) * sizeof(Sommet_ville));
    sommet->sommets[sommet->n_sommets++]=sommet_quelconque;
    G->sommets[sommet->n_sommets++]=sommet_quelconque;
    G->sommets[sommet->n_sommets++].ID=sommet->n_sommets;

}
void seisme(Sommet_ville* sommet_seisme, int seisme_impact, Tab_sommets* sommet, Graphe* G){
    //Effectuer la catstrophe sur une ville de manière aléatoire

    srand(time(NULL));
    int ville_aleatoire=rand()% G->sommets_TAB->n_sommets;
    float magnitude=0.0 + (rand() / (float)RAND_MAX) * (10.0 - 0.0);
    

    for(int i=0;i<sommet->n_bats; i++){

        if(magnitude<5.0){
            seisme_impact=0;
        }

        else if(magnitude>=5.0 && magnitude<=5.9){
            seisme_impact=1;
        }
        else if(magnitude>=6.0 && magnitude<=6.9){
            seisme_impact=5;
        }
        else if(magnitude>=7.0 && magnitude<=7.9){
            seisme_impact=20;
        }

        else if(magnitude>=8.0){
            seisme_impact=90;
            sommet_seisme[ville_aleatoire].batiment[i].etage=0;
            sommet_seisme->population=-1000;
        }
        if(sommet_seisme[ville_aleatoire].batiment[i].etat>60){
            seisme_impact=seisme_impact-1;
        }
        sommet_seisme[ville_aleatoire].batiment[i].etat=sommet_seisme[ville_aleatoire].batiment[i].etat-seisme_impact;

        for(int j=0; j<sommet->n_sommets; j++){
            G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat=G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat-seisme_impact;
            G->chemins[sommet_seisme[ville_aleatoire].ID][j].capacité= G->chemins[sommet_seisme[ville_aleatoire].ID][j].capacité-seisme_impact;

            if(G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat==0){
                strcpy(G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat_actuel, "detruite");
            }

            if(G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat<50 && G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat>0){
                strcpy(G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat_actuel, "endommagée");
            }
        }

        if(sommet_seisme[ville_aleatoire].batiment[i].etat==0){
            supprimer_Bat(sommet, sommet_seisme[ville_aleatoire].batiment,sommet_seisme, G);
            strcpy(sommet_seisme[ville_aleatoire].batiment[i].etat_courant, "détruit");
        }     
    }
}

void verifier_accessibilite(Graphe* G, int ID_sommet_debut){

    srand(time(NULL));
    ID_sommet_debut=rand()% G->sommets_TAB->n_sommets;

    for(int j=0; j<G->sommets_TAB->n_sommets; j++){
        if(G->chemins[ID_sommet_debut][j].etat==0)
        {
            printf("Le sommet %s est inaccessible en partant du sommet %s", G->sommets[j].nom, G->sommets[ID_sommet_debut].nom);
        }
        else if(G->chemins[ID_sommet_debut][j].etat>0){
            printf("Le sommet %s est accessible en partant du sommet %s", G->sommets[j].nom, G->sommets[ID_sommet_debut].nom);
        }
    }
    
}
void afficher_route(Graphe* G){

    srand(time(NULL));
    int ID_sommet_debut=rand()% G->sommets_TAB->n_sommets;

    for(int j=0; j<G->sommets_TAB->n_sommets; j++){
        if(G->chemins[ID_sommet_debut][j].etat>0){
        printf("Pour la Route allant de %s à %s\n Distance: %d\n  Etat:%d\n  Capacité:%d\n", G->sommets[ID_sommet_debut].nom, G->sommets[j].nom, G->chemins[ID_sommet_debut][j].distance,  G->chemins[ID_sommet_debut][j].etat, G->chemins[ID_sommet_debut][j].capacité);
        printf("\n");
        }
    }
}
Sommet_ville rechercher_etat_ville(Graphe* G, int id_ville_recherchee){

    for(int i=0; i<G->sommets_TAB->n_sommets; i++){
        if(G->sommets[i].ID==id_ville_recherchee)
        return G->sommets[i];
    }
}


void ville_connectee(Graphe* G, int sommet, int* sommet_parcouru, int groupe_id) {
        sommet_parcouru[sommet] = groupe_id;
    
        for (int i = 0; i < G->sommets_TAB->n_sommets; i++) {
            if (G->chemins[sommet][i].etat > 0 && sommet_parcouru[i] == 0) {
                ville_connectee(G, i, sommet_parcouru, groupe_id);
            }
        }
    }
    
void afficher_groupes_connexes(Graphe* G) {

        int n = G->sommets_TAB->n_sommets;
        int sommet_parcouru[taille_max] = {0};
        int groupe_id = 1;
    
        for (int i = 0; i < n; i++) {
            if (sommet_parcouru[i] == 0) {
                ville_connectee(G, i, sommet_parcouru, groupe_id);
                groupe_id++;
            }
        }
    
        for (int j = 1; j < groupe_id; j++) {
            printf("Groupe %d : ", j);
            for (int i = 0; i < n; i++) {
                if (sommet_parcouru[i] == j) {
                    printf("%s ", G->sommets[i].nom);
                }
            }
            printf("\n");
        }
    }