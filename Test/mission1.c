#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include <time.h>

void initialiser_graphe_entier(Graphe *G)
{
    for (int i = 0; i < taille_max; i++)
    {
        for (int g = 0; g < taille_max; g++)
        {
            G->chemins[i][g].distance = 0;
            G->chemins[i][g].etat = 0;
            G->chemins[i][g].capacité = 0;
        }
    }
}

void ajouter_sommet(Tab_sommets* sommet,Graphe* G, Sommet_ville sommet_quelconque){
   
   
    sommet->sommets=realloc(sommet->sommets, (sommet->n_sommets + 1) * sizeof(Sommet_ville));
    sommet->sommets[sommet->n_sommets]=sommet_quelconque;
    sommet->n_sommets++;

    G->sommets[sommet->n_sommets]=sommet_quelconque;
    G->sommets[sommet->n_sommets].ID=sommet_quelconque.ID;

    for(int i=0; i<1000; i++){  
        Bat nouveau_bat;
        nouveau_bat.etat=100;
        int etage_aleatoire=rand()%7;

            if(etage_aleatoire>3){
                nouveau_bat.etage=10;
                nouveau_bat.appartements=nouveau_bat.etage*11;
                nouveau_bat.capacite=nouveau_bat.appartements*4;
            }
            else if(etage_aleatoire>1 &&  etage_aleatoire<=3){
                nouveau_bat.etage=7;
                nouveau_bat.appartements=nouveau_bat.etage*8;
                nouveau_bat.capacite=nouveau_bat.appartements*4;
            }
            else if(etage_aleatoire<=1){
                nouveau_bat.etage=5;
                nouveau_bat.appartements=nouveau_bat.etage*6;
                nouveau_bat.capacite=nouveau_bat.appartements*4;
            }

        ajouter_bat(nouveau_bat, sommet_quelconque.ID, G->sommets_TAB, G);
    }
   
}

Graphe *Creation_graphe(int nsommets)
{
    Graphe *G = malloc(sizeof(Graphe));
    if (!G)
    {
        perror("Erreur d'allocation mémoire pour le graphe");
        exit(EXIT_FAILURE);
    }

    G->sommets_TAB = malloc(sizeof(Tab_sommets));
    if (!G->sommets_TAB)
    {
        perror("Erreur d'allocation mémoire pour sommets_TAB");
        exit(EXIT_FAILURE);
    }

    G->sommets_TAB->sommets = malloc(nsommets * sizeof(Sommet_ville));
    G->sommets_TAB->n_sommets = 0;
    G->sommets_TAB->n_bats = 0;

    G->chemins = malloc(nsommets * sizeof(Route *));
    for (int i = 0; i < nsommets; i++)
    {
        G->chemins[i] = malloc(nsommets * sizeof(Route));
    }

    for (int i = 0; i < nsommets; i++)
    {
        int sommet_aleatoire = rand() % 100;
        Sommet_ville sommet_ajoutee;
        sommet_ajoutee.ID = i;
        sommet_ajoutee.n_bats = 0;

        if (sommet_aleatoire < 50)
        {
            strcpy(sommet_ajoutee.type, "Ville");
            sprintf(sommet_ajoutee.nom, "Ville S%d", sommet_ajoutee.ID);
            sommet_ajoutee.population = 100000;
        }
        else if (sommet_aleatoire < 75)
        {
            strcpy(sommet_ajoutee.type, "Hopital");
            sprintf(sommet_ajoutee.nom, "Hopital S%d", sommet_ajoutee.ID);
            sommet_ajoutee.population = 200;
            sommet_ajoutee.etat = 100;
        }
        else
        {
            strcpy(sommet_ajoutee.type, "Entrepot");
            sprintf(sommet_ajoutee.nom, "Entrepot S%d", sommet_ajoutee.ID);
            sommet_ajoutee.etat = 100;
        }

        ajouter_sommet(G->sommets_TAB, sommet_ajoutee);
    }

    initialiser_graphe_entier(G);

    for (int i = 0; i < nsommets; i++)
    {
        for (int j = 0; j < nsommets; j++)
        {
            if (i != j && rand() % 3 == 0)
            {
                int distance = rand() % 100;
                creation_route(G, i, j, distance);
                creation_route(G, j, i, distance);
            }
        }
    }

    return G;
}

void creation_route(Graphe *G, int id_depart, int id_arrivee, int distance_voulue)
{

    int capacite_valeurs[] = {1, 2, 3, 4, 5, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 9, 10};
    int taille_tab_capacite = sizeof(capacite_valeurs) / sizeof(capacite_valeurs[0]);
    int capacite_aleatoire = rand() % taille_tab_capacite;
    int capacite = capacite_valeurs[capacite_aleatoire];

    G->chemins[id_depart][id_arrivee].distance = distance_voulue;
    G->chemins[id_depart][id_arrivee].capacité = capacite;
    G->chemins[id_depart][id_arrivee].etat = 100;
}

void initialiser_tableau_batiment(Tab_sommets *tableau_bats_sommets, int nombre)
{
    tableau_bats_sommets->batiments = malloc(nombre * sizeof(Bat));
    tableau_bats_sommets->n_bats = 0;
}

void ajouter_bat(Bat batiment, Tab_sommets *tab, Graphe *G, int id_sommet)
{
    if (id_sommet >= G->sommets_TAB->n_sommets)
        return;

    Sommet_ville *sommet = &G->sommets_TAB->sommets[id_sommet];

    sommet->batiment = realloc(sommet->batiment, (sommet->n_bats + 1) * sizeof(Bat));
    sommet->batiment[sommet->n_bats++] = batiment;

    tab->batiments = realloc(tab->batiments, (tab->n_bats + 1) * sizeof(Bat));
    tab->batiments[tab->n_bats++] = batiment;
}

void supprimer_Bat(Tab_sommets *tab, Bat *bat_a_supprimer, Sommet_ville *sommet)
{
    int index = -1;
    for (int i = 0; i < tab->n_bats; i++)
    {
        if (&tab->batiments[i] == bat_a_supprimer)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return;

    for (int i = index; i < tab->n_bats - 1; i++)
    {
        tab->batiments[i] = tab->batiments[i + 1];
    }
    tab->n_bats--;
    tab->batiments = realloc(tab->batiments, tab->n_bats * sizeof(Bat));
}

void seisme(Sommet_ville *sommet_seisme, int seisme_impact, Tab_sommets *sommet, Graphe *G)
{
    // Effectuer la catstrophe sur une ville de manière aléatoire
    int ville_aleatoire = rand() % G->sommets_TAB->n_sommets;
    float magnitude = 0.0 + (rand() / (float)RAND_MAX) * (10.0 - 0.0);

    for (int i = 0; i < sommet->n_bats; i++)
    {

        if (magnitude < 5.0)
        {
            seisme_impact = 0;
        }

        else if (magnitude >= 5.0 && magnitude <= 5.9)
        {
            seisme_impact = 1;
        }
        else if (magnitude >= 6.0 && magnitude <= 6.9)
        {
            seisme_impact = 5;
        }
        else if (magnitude >= 7.0 && magnitude <= 7.9)
        {
            seisme_impact = 20;
        }

        else if (magnitude >= 8.0)
        {
            seisme_impact = 90;
            sommet_seisme[ville_aleatoire].batiment[i].etage = 0;
            sommet_seisme->population -= 1000;
        }
        if (sommet_seisme[ville_aleatoire].batiment[i].etat > 60)
        {
            seisme_impact = seisme_impact - 1;
        }
        sommet_seisme[ville_aleatoire].batiment[i].etat = sommet_seisme[ville_aleatoire].batiment[i].etat - seisme_impact;

        for (int j = 0; j < sommet->n_sommets; j++)
        {
            G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat = G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat - seisme_impact;
            G->chemins[sommet_seisme[ville_aleatoire].ID][j].capacité = G->chemins[sommet_seisme[ville_aleatoire].ID][j].capacité - seisme_impact;
            if (G->chemins[sommet_seisme[ville_aleatoire].ID][j].etat == 0)
            {
            }

            if (sommet_seisme[ville_aleatoire].batiment[i].etat == 0)
            {
                supprimer_Bat(sommet, sommet_seisme[ville_aleatoire].batiment, sommet_seisme);
            }
        }
    }
}

void verifier_accessibilite(Graphe *G, int ID_sommet_debut)
{
    /*srand(time(NULL));
    ID_sommet_debut = rand() % G->sommets_TAB->n_sommets;
*/
    for (int j = 0; j < G->sommets_TAB->n_sommets; j++)
    {
        if (G->chemins[ID_sommet_debut][j].etat == 0)
        {
            printf("Le sommet %s est inacessible en partant du sommet %s", 
                    G->sommets[ID_sommet_debut].nom, 
                    G->sommets[j].nom);
        }
        else
        {
            printf("Le sommet %s est accessible depuis %s\n",
                   G->sommets[j].nom,
                   G->sommets[ID_sommet_debut].nom);
        }
    }
}
void afficher_route(Graphe *G, int ID_sommet_debut)
{
    /*srand(time(NULL));
    ID_sommet_debut = rand() % G->sommets_TAB->n_sommets;*/

    /*for (int j = 0; j < G->sommets_TAB->n_sommets; j++)
    {
        if (G->chemins[ID_sommet_debut][j].etat > 0)
        {
            printf("Pour la Route allant de %s à %s\n Distance: %d\n  Etat:%d\n  Capacité:%d\n", G->sommets[ID_sommet_debut].nom, G->sommets[j].nom, G->chemins[ID_sommet_debut][j].distance, G->chemins[ID_sommet_debut][j].etat, G->chemins[ID_sommet_debut][j].capacité);
            printf("\n");
        }
    }*/

    for (int j = 0; j < G->sommets_TAB->n_sommets; j++)
    {
        if (G->chemins[ID_sommet_debut][j].etat > 0)
        {
            printf("Route de %s à %s : Distance=%d, État=%d, Capacité=%d\n",
                   G->sommets[ID_sommet_debut].nom,
                   G->sommets[j].nom,
                   G->chemins[ID_sommet_debut][j].distance,
                   G->chemins[ID_sommet_debut][j].etat,
                   G->chemins[ID_sommet_debut][j].capacité);
        }
    }
}
